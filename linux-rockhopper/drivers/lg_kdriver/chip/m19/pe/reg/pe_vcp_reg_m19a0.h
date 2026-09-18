#ifndef _PE_VCP_REG_M19A0_H_
#define _PE_VCP_REG_M19A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc900c400L VCP_DISP_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mask_pic_init_y_mux_u0_cdc         :1 ,	//0 
	mask_pic_init_c_mux_u0_cdc         :1 ,	//1 
	mask_pic_init_y_mux_u1_cdc         :1 ,	//2 
	mask_pic_init_c_mux_u1_cdc         :1 ,	//3 
	reserved01                         :4 ,	//reserved
	mask_pic_init_y_mux_m_wcp          :1 ,	//8 
	mask_pic_init_c_mux_m_wcp          :1 ,	//9 
	mask_pic_init_y_mux_s_wcp          :1 ,	//10
	mask_pic_init_c_mux_s_wcp          :1 ,	//11
	mask_pic_init_y_mux_ms_wcp         :1 ,	//12
	mask_pic_init_c_mux_ms_wcp         :1 ,	//13
	reserved02                         :2 ,	//reserved
	mask_pic_start_y_mux_u0_cdc        :1 ,	//16
	mask_pic_start_c_mux_u0_cdc        :1 ,	//17
	mask_pic_start_y_mux_u1_cdc        :1 ,	//18
	mask_pic_start_c_mux_u1_cdc        :1 ,	//19
	reserved03                         :4 ,	//reserved
	mask_pic_start_y_mux_m_wcp         :1 ,	//24
	mask_pic_start_c_mux_m_wcp         :1 ,	//25
	mask_pic_start_y_mux_s_wcp         :1 ,	//26
	mask_pic_start_c_mux_s_wcp         :1 ;	//27
}PE_M19_VCP_DISP_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c404L VCP_DISP_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_DISP_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c408L VCP_DISP_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_inverse_3d_lr                  :1 ,	//0 
	reserved01                         :3 ,	//reserved
	wcp_m_mix_enable                   :2 ,	//5:4
	cg_disable                         :1 ,	//6 
	reserved02                         :1 ,	//reserved
	en_bypass_sync_my                  :1 ,	//8 
	en_bypass_sync_mc                  :1 ,	//9 
	en_bypass_sync_sy                  :1 ,	//10
	en_bypass_sync_sc                  :1 ;	//11
}PE_M19_VCP_DISP_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c40cL VCP_DISP_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_DISP_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc900c410L VCP_CDC_MV_SYNC_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	u0_cdc_y_sync_sel                  :2 ,	//1:0
	u0_cdc_c_sync_sel                  :2 ,	//3:2
	u1_cdc_y_sync_sel                  :2 ,	//5:4
	u1_cdc_c_sync_sel                  :2 ,	//7:6
	reserved01                         :8 ,	//reserved
	mon_u0_cdc_y_pi_ps_pos_sel         :2 ,	//17:16
	mon_u0_cdc_c_pi_ps_pos_sel         :2 ,	//19:18
	mon_u1_cdc_y_pi_ps_pos_sel         :2 ,	//21:20
	mon_u1_cdc_c_pi_ps_pos_sel         :2 ;	//23:22
}PE_M19_VCP_CDC_MV_SYNC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c414L VCP_CDC_MV_RST_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	u0_cdc_y_disp_sreset               :1 ,	//0 
	u0_cdc_c_disp_sreset               :1 ,	//1 
	u1_cdc_y_disp_sreset               :1 ,	//2 
	u1_cdc_c_disp_sreset               :1 ;	//3 
}PE_M19_VCP_CDC_MV_RST_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c420L VCP_U0_WIN_O_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_pos_x                    :13;	//28:16
}PE_M19_VCP_U0_WIN_O_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c424L VCP_U0_WIN_O_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y                   :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_size_x                   :13;	//28:16
}PE_M19_VCP_U0_WIN_O_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c428L VCP_U0_PG_PAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	//reserved
	ramp_pat_en                        :2 ,	//5:4
	mpg_o_color_sel                    :2 ,	//7:6
	reserved02                         :8 ,	//reserved
	peaking_en                         :1 ,	//16
	peak_min_max_clip                  :1 ,	//17
	reserved03                         :2 ,	//reserved
	peak_even_odd_sel                  :1 ,	//20
	reg_odd_size_dbg                   :1 ,	//21
	reserved04                         :2 ,	//reserved
	peak_gain                          :8 ;	//31:24
}PE_M19_VCP_U0_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c42cL VCP_U0_PG_PEAK_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	peak_hsize                         :13;	//12:0
}PE_M19_VCP_U0_PG_PEAK_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c430L VCP_U0_CDC_Y_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	//4:0
	cdc_rdy_ctrl                       :1 ,	//5 
	cdc_auto_v_half                    :1 ,	//6 
	cdc_black_mask                     :1 ,	//7 
	cdc_vmode                          :3 ,	//10:8
	cdc_vmode_cnt_sel                  :1 ,	//11
	cdc_scan_type                      :3 ,	//14:12
	reserved01                         :1 ,	//reserved
	cdc_hmode                          :3 ,	//18:16
	cdc_hmode_cnt_sel                  :1 ,	//19
	cdc_ch                             :2 ,	//21:20
	cdc_de_mode                        :1 ,	//22
	reserved02                         :1 ,	//reserved
	cdc_format                         :4 ,	//27:24
	cdc_lsb_omode                      :4 ;	//31:28
}PE_M19_VCP_U0_CDC_Y_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c434L VCP_U0_CDC_Y_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	//7:0
	nactive_color_cb                   :8 ,	//15:8
	nactive_color_y                    :8 ,	//23:16
	nactive_window_end_ctrl            :3 ,	//26:24
	reserved01                         :1 ,	//reserved
	nactive_window_start_ctrl          :3 ,	//30:28
	nactive_color_enable               :1 ;	//31
}PE_M19_VCP_U0_CDC_Y_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c438L VCP_U0_CDC_Y_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_u0_cdc          :4 ,	//3:0
	set_pic_start_y_mux_u0_cdc         :4 ,	//7:4
	sel_de_type                        :2 ,	//9:8
	sel_de_type_manual                 :1 ,	//10
	reserved01                         :5 ,	//reserved
	cdc_xpos_end                       :14,	//29:16
	reserved02                         :1 ,	//reserved
	en_sel_cdc_xpos_end                :1 ;	//31
}PE_M19_VCP_U0_CDC_Y_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c43cL VCP_U0_CDC_Y_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_U0_CDC_Y_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c440L VCP_U0_CDC_C_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	//4:0
	cdc_rdy_ctrl                       :1 ,	//5 
	cdc_auto_v_half                    :1 ,	//6 
	cdc_black_mask                     :1 ,	//7 
	cdc_vmode                          :3 ,	//10:8
	cdc_vmode_cnt_sel                  :1 ,	//11
	cdc_scan_type                      :3 ,	//14:12
	reserved01                         :1 ,	//reserved
	cdc_hmode                          :3 ,	//18:16
	cdc_hmode_cnt_sel                  :1 ,	//19
	cdc_ch                             :2 ,	//21:20
	cdc_de_mode                        :1 ,	//22
	reserved02                         :1 ,	//reserved
	cdc_format                         :4 ,	//27:24
	cdc_lsb_omode                      :4 ;	//31:28
}PE_M19_VCP_U0_CDC_C_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c444L VCP_U0_CDC_C_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	//7:0
	nactive_color_cb                   :8 ,	//15:8
	nactive_color_y                    :8 ,	//23:16
	nactive_window_end_ctrl            :3 ,	//26:24
	reserved01                         :1 ,	//reserved
	nactive_window_start_ctrl          :3 ,	//30:28
	nactive_color_enable               :1 ;	//31
}PE_M19_VCP_U0_CDC_C_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c448L VCP_U0_CDC_C_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_c_mux_u0_cdc          :4 ,	//3:0
	set_pic_start_c_mux_u0_cdc         :4 ,	//7:4
	sel_de_type                        :2 ,	//9:8
	sel_de_type_manual                 :1 ,	//10
	reserved01                         :5 ,	//reserved
	cdc_xpos_end                       :14,	//29:16
	reserved02                         :1 ,	//reserved
	en_sel_cdc_xpos_end                :1 ;	//31
}PE_M19_VCP_U0_CDC_C_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c44cL VCP_U0_CDC_C_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_U0_CDC_C_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c450L VCP_U1_WIN_O_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_pos_x                    :13;	//28:16
}PE_M19_VCP_U1_WIN_O_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c454L VCP_U1_WIN_O_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y                   :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_size_x                   :13;	//28:16
}PE_M19_VCP_U1_WIN_O_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c458L VCP_U1_PG_PAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	//reserved
	ramp_pat_en                        :2 ,	//5:4
	mpg_o_color_sel                    :2 ,	//7:6
	reserved02                         :8 ,	//reserved
	peaking_en                         :1 ,	//16
	peak_min_max_clip                  :1 ,	//17
	reserved03                         :2 ,	//reserved
	peak_even_odd_sel                  :1 ,	//20
	reg_odd_size_dbg                   :1 ,	//21
	reserved04                         :2 ,	//reserved
	peak_gain                          :8 ;	//31:24
}PE_M19_VCP_U1_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c45cL VCP_U1_PG_PEAK_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	peak_hsize                         :13;	//12:0
}PE_M19_VCP_U1_PG_PEAK_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c460L VCP_U1_CDC_Y_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	//4:0
	cdc_rdy_ctrl                       :1 ,	//5 
	cdc_auto_v_half                    :1 ,	//6 
	cdc_black_mask                     :1 ,	//7 
	cdc_vmode                          :3 ,	//10:8
	cdc_vmode_cnt_sel                  :1 ,	//11
	cdc_scan_type                      :3 ,	//14:12
	reserved01                         :1 ,	//reserved
	cdc_hmode                          :3 ,	//18:16
	cdc_hmode_cnt_sel                  :1 ,	//19
	cdc_ch                             :2 ,	//21:20
	cdc_de_mode                        :1 ,	//22
	reserved02                         :1 ,	//reserved
	cdc_format                         :4 ,	//27:24
	cdc_lsb_omode                      :4 ;	//31:28
}PE_M19_VCP_U1_CDC_Y_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c464L VCP_U1_CDC_Y_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	//7:0
	nactive_color_cb                   :8 ,	//15:8
	nactive_color_y                    :8 ,	//23:16
	nactive_window_end_ctrl            :3 ,	//26:24
	reserved01                         :1 ,	//reserved
	nactive_window_start_ctrl          :3 ,	//30:28
	nactive_color_enable               :1 ;	//31
}PE_M19_VCP_U1_CDC_Y_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c468L VCP_U1_CDC_Y_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_u1_cdc          :4 ,	//3:0
	set_pic_start_y_mux_u1_cdc         :4 ,	//7:4
	sel_de_type                        :2 ,	//9:8
	sel_de_type_manual                 :1 ,	//10
	reserved01                         :5 ,	//reserved
	cdc_xpos_end                       :14,	//29:16
	reserved02                         :1 ,	//reserved
	en_sel_cdc_xpos_end                :1 ;	//31
}PE_M19_VCP_U1_CDC_Y_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c46cL VCP_U1_CDC_Y_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_U1_CDC_Y_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c470L VCP_U1_CDC_C_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	//4:0
	cdc_rdy_ctrl                       :1 ,	//5 
	cdc_auto_v_half                    :1 ,	//6 
	cdc_black_mask                     :1 ,	//7 
	cdc_vmode                          :3 ,	//10:8
	cdc_vmode_cnt_sel                  :1 ,	//11
	cdc_scan_type                      :3 ,	//14:12
	reserved01                         :1 ,	//reserved
	cdc_hmode                          :3 ,	//18:16
	cdc_hmode_cnt_sel                  :1 ,	//19
	cdc_ch                             :2 ,	//21:20
	cdc_de_mode                        :1 ,	//22
	reserved02                         :1 ,	//reserved
	cdc_format                         :4 ,	//27:24
	cdc_lsb_omode                      :4 ;	//31:28
}PE_M19_VCP_U1_CDC_C_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c474L VCP_U1_CDC_C_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	//7:0
	nactive_color_cb                   :8 ,	//15:8
	nactive_color_y                    :8 ,	//23:16
	nactive_window_end_ctrl            :3 ,	//26:24
	reserved01                         :1 ,	//reserved
	nactive_window_start_ctrl          :3 ,	//30:28
	nactive_color_enable               :1 ;	//31
}PE_M19_VCP_U1_CDC_C_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c478L VCP_U1_CDC_C_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_c_mux_u1_cdc          :4 ,	//3:0
	set_pic_start_c_mux_u1_cdc         :4 ,	//7:4
	sel_de_type                        :2 ,	//9:8
	sel_de_type_manual                 :1 ,	//10
	reserved01                         :5 ,	//reserved
	cdc_xpos_end                       :14,	//29:16
	reserved02                         :1 ,	//reserved
	en_sel_cdc_xpos_end                :1 ;	//31
}PE_M19_VCP_U1_CDC_C_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c47cL VCP_U1_CDC_C_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_U1_CDC_C_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c480L VCP_U0_WIN_O_POS_AUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y_aux                :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_pos_x_aux                :13;	//28:16
}PE_M19_VCP_U0_WIN_O_POS_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c484L VCP_U0_WIN_O_SIZE_AUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y_aux               :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_size_x_aux               :13,	//28:16
	reserved02                         :2 ,	//reserved
	cdc_win_aux_auto                   :1 ;	//31
}PE_M19_VCP_U0_WIN_O_SIZE_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c488L VCP_U1_WIN_O_POS_AUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y_aux                :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_pos_x_aux                :13;	//28:16
}PE_M19_VCP_U1_WIN_O_POS_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c48cL VCP_U1_WIN_O_SIZE_AUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y_aux               :13,	//12:0
	reserved01                         :3 ,	//reserved
	cdc_win_o_size_x_aux               :13,	//28:16
	reserved02                         :2 ,	//reserved
	cdc_win_aux_auto                   :1 ;	//31
}PE_M19_VCP_U1_WIN_O_SIZE_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e0L VCP_SG_MVY_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	//15:0
	vfp                                :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e4L VCP_SG_MVY_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	//15:0
	vbp                                :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e8L VCP_SG_MVY_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	//15:0
	hfp                                :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c4ecL VCP_SG_MVY_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	//15:0
	hbp                                :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f0L VCP_SG_MVY_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	//15:0
	sync_i_h_sel                       :1 ,	//16
	sync_i_v_sel                       :1 ,	//17
	sync_i_inv_ha                      :1 ,	//18
	sync_i_inv_va                      :1 ,	//19
	sync_o_sel_ha                      :1 ,	//20
	sync_o_sel_va                      :1 ,	//21
	sync_o_sel_hs                      :1 ,	//22
	sync_o_sel_vs                      :1 ,	//23
	tp_update_hv_zero                  :1 ,	//24
	reserved01                         :3 ,	//reserved
	manual_cnt_h_value_en              :1 ,	//28
	manual_cnt_v_value_en              :1 ,	//29
	reserved02                         :1 ,	//reserved
	update_force                       :1 ;	//31
}PE_M19_VCP_SG_MVY_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f4L VCP_SG_MVY_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	//15:0
	sync_v_dly                         :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f8L VCP_SG_MVY_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	//15:0
	manual_cnt_v_value                 :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c4fcL VCP_SG_MVY_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_va_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_MVY_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c500L VCP_SG_MVY_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_vs_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_MVY_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c504L VCP_SG_MVY_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//31:0
}PE_M19_VCP_SG_MVY_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c510L VCP_SG_MVC_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	//15:0
	vfp                                :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c514L VCP_SG_MVC_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	//15:0
	vbp                                :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c518L VCP_SG_MVC_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	//15:0
	hfp                                :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c51cL VCP_SG_MVC_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	//15:0
	hbp                                :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c520L VCP_SG_MVC_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	//15:0
	sync_i_h_sel                       :1 ,	//16
	sync_i_v_sel                       :1 ,	//17
	sync_i_inv_ha                      :1 ,	//18
	sync_i_inv_va                      :1 ,	//19
	sync_o_sel_ha                      :1 ,	//20
	sync_o_sel_va                      :1 ,	//21
	sync_o_sel_hs                      :1 ,	//22
	sync_o_sel_vs                      :1 ,	//23
	tp_update_hv_zero                  :1 ,	//24
	reserved01                         :3 ,	//reserved
	manual_cnt_h_value_en              :1 ,	//28
	manual_cnt_v_value_en              :1 ,	//29
	reserved02                         :1 ,	//reserved
	update_force                       :1 ;	//31
}PE_M19_VCP_SG_MVC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c524L VCP_SG_MVC_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	//15:0
	sync_v_dly                         :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c528L VCP_SG_MVC_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	//15:0
	manual_cnt_v_value                 :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c52cL VCP_SG_MVC_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_va_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_MVC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c530L VCP_SG_MVC_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_vs_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_MVC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c534L VCP_SG_MVC_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//31:0
}PE_M19_VCP_SG_MVC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c538L MON_VCP_U0Y_PIC_INIT_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0y_pic_init_hpos              :16,	//15:0
	vcp_u0y_pic_init_vpos              :16;	//31:16
}PE_M19_MON_VCP_U0Y_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c53cL MON_VCP_U0Y_PIC_START_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0y_pic_start_hpos             :16,	//15:0
	vcp_u0y_pic_start_vpos             :16;	//31:16
}PE_M19_MON_VCP_U0Y_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c540L MON_VCP_U0C_PIC_INIT_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0c_pic_init_hpos              :16,	//15:0
	vcp_u0c_pic_init_vpos              :16;	//31:16
}PE_M19_MON_VCP_U0C_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c544L MON_VCP_U0C_PIC_START_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0c_pic_start_hpos             :16,	//15:0
	vcp_u0c_pic_start_vpos             :16;	//31:16
}PE_M19_MON_VCP_U0C_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c548L MON_VCP_U1Y_PIC_INIT_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1y_pic_init_hpos              :16,	//15:0
	vcp_u1y_pic_init_vpos              :16;	//31:16
}PE_M19_MON_VCP_U1Y_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c54cL MON_VCP_U1Y_PIC_START_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1y_pic_start_hpos             :16,	//15:0
	vcp_u1y_pic_start_vpos             :16;	//31:16
}PE_M19_MON_VCP_U1Y_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c550L MON_VCP_U1C_PIC_INIT_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1c_pic_init_hpos              :16,	//15:0
	vcp_u1c_pic_init_vpos              :16;	//31:16
}PE_M19_MON_VCP_U1C_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c554L MON_VCP_U1C_PIC_START_POS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1c_pic_start_hpos             :16,	//15:0
	vcp_u1c_pic_start_vpos             :16;	//31:16
}PE_M19_MON_VCP_U1C_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c560L VCP_SG_SVY_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	//15:0
	vfp                                :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c564L VCP_SG_SVY_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	//15:0
	vbp                                :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c568L VCP_SG_SVY_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	//15:0
	hfp                                :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c56cL VCP_SG_SVY_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	//15:0
	hbp                                :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c570L VCP_SG_SVY_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	//15:0
	sync_i_h_sel                       :1 ,	//16
	sync_i_v_sel                       :1 ,	//17
	sync_i_inv_ha                      :1 ,	//18
	sync_i_inv_va                      :1 ,	//19
	sync_o_sel_ha                      :1 ,	//20
	sync_o_sel_va                      :1 ,	//21
	sync_o_sel_hs                      :1 ,	//22
	sync_o_sel_vs                      :1 ,	//23
	tp_update_hv_zero                  :1 ,	//24
	reserved01                         :3 ,	//reserved
	manual_cnt_h_value_en              :1 ,	//28
	manual_cnt_v_value_en              :1 ,	//29
	reserved02                         :1 ,	//reserved
	update_force                       :1 ;	//31
}PE_M19_VCP_SG_SVY_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c574L VCP_SG_SVY_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	//15:0
	sync_v_dly                         :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c578L VCP_SG_SVY_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	//15:0
	manual_cnt_v_value                 :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c57cL VCP_SG_SVY_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_va_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_SVY_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c580L VCP_SG_SVY_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_vs_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_SVY_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c584L VCP_SG_SVY_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//31:0
}PE_M19_VCP_SG_SVY_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c590L VCP_SG_SVC_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	//15:0
	vfp                                :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c594L VCP_SG_SVC_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	//15:0
	vbp                                :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c598L VCP_SG_SVC_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	//15:0
	hfp                                :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c59cL VCP_SG_SVC_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	//15:0
	hbp                                :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c5a0L VCP_SG_SVC_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	//15:0
	sync_i_h_sel                       :1 ,	//16
	sync_i_v_sel                       :1 ,	//17
	sync_i_inv_ha                      :1 ,	//18
	sync_i_inv_va                      :1 ,	//19
	sync_o_sel_ha                      :1 ,	//20
	sync_o_sel_va                      :1 ,	//21
	sync_o_sel_hs                      :1 ,	//22
	sync_o_sel_vs                      :1 ,	//23
	tp_update_hv_zero                  :1 ,	//24
	reserved01                         :3 ,	//reserved
	manual_cnt_h_value_en              :1 ,	//28
	manual_cnt_v_value_en              :1 ,	//29
	reserved02                         :1 ,	//reserved
	update_force                       :1 ;	//31
}PE_M19_VCP_SG_SVC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c5a4L VCP_SG_SVC_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	//15:0
	sync_v_dly                         :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c5a8L VCP_SG_SVC_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	//15:0
	manual_cnt_v_value                 :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c5acL VCP_SG_SVC_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_va_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_SVC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c5b0L VCP_SG_SVC_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	//14:0
	auto_general_en                    :1 ,	//15
	auto_vs_delay                      :15,	//30:16
	auto_seamless                      :1 ;	//31
}PE_M19_VCP_SG_SVC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c5b4L VCP_SG_SVC_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//31:0
}PE_M19_VCP_SG_SVC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c5b8L VCP_WCP_M_DISP_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pg1ch_win_o_size_y                 :13,	//12:0
	reserved01                         :3 ,	//reserved
	pg1ch_win_o_size_x                 :13;	//28:16
}PE_M19_VCP_WCP_M_DISP_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c5bcL VCP_WCP_M_PG_PAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lattice_pat_en                     :1 ,	//0 
	reserved01                         :3 ,	//reserved
	ramp_pat_en                        :2 ,	//5:4
	mpg_o_color_sel                    :2 ,	//7:6
	border_sel                         :4 ,	//11:8
	reserved02                         :3 ,	//reserved
	status_bar_en                      :1 ,	//15
	reserved03                         :4 ,	//reserved
	status0_00_src_sel                 :2 ,	//21:20
	status0_01_src_sel                 :2 ,	//23:22
	status0_02_src_sel                 :2 ,	//25:24
	status0_03_src_sel                 :2 ,	//27:26
	cg_disable                         :1 ,	//28
	reserved04                         :2 ,	//reserved
	mean_fil_en                        :1 ;	//31
}PE_M19_VCP_WCP_M_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c5c0L VCP_WCP_S_DISP_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pg1ch_win_o_size_y                 :13,	//12:0
	reserved01                         :3 ,	//reserved
	pg1ch_win_o_size_x                 :13;	//28:16
}PE_M19_VCP_WCP_S_DISP_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c5c4L VCP_WCP_S_PG_PAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lattice_pat_en                     :1 ,	//0 
	reserved01                         :3 ,	//reserved
	ramp_pat_en                        :2 ,	//5:4
	mpg_o_color_sel                    :2 ,	//7:6
	border_sel                         :4 ,	//11:8
	reserved02                         :16,	//reserved
	cg_disable                         :1 ,	//28
	reserved03                         :2 ,	//reserved
	mean_fil_en                        :1 ;	//31
}PE_M19_VCP_WCP_S_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c5c8L VCP_WCP_M_PIXEL_READ_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rd_pel_pos_y                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	rd_pel_pos_x                       :12,	//27:16
	reserved02                         :3 ,	//reserved
	rd_pel_pat_en                      :1 ;	//31
}PE_M19_VCP_WCP_M_PIXEL_READ_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c5ccL VCP_WCP_M_PIXEL_READ_CTRL_AUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rd_pel_pos_y                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	rd_pel_pos_x                       :12,	//27:16
	reserved02                         :3 ,	//reserved
	rd_pel_pat_en                      :1 ;	//31
}PE_M19_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c5d0L VCP_WCP_M_LINE_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	even_line_cr                       :8 ,	//7:0
	even_line_cb                       :8 ,	//15:8
	even_line_y                        :8 ,	//23:16
	reserved01                         :7 ,	//reserved
	even_line_pat_en                   :1 ;	//31
}PE_M19_VCP_WCP_M_LINE_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c5d4L VCP_WCP_M_LINE_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_line_cr                        :8 ,	//7:0
	odd_line_cb                        :8 ,	//15:8
	odd_line_y                         :8 ,	//23:16
	reserved01                         :7 ,	//reserved
	odd_line_pat_en                    :1 ;	//31
}PE_M19_VCP_WCP_M_LINE_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c5d8L VCP_WCP_S_LINE_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	even_line_cr                       :8 ,	//7:0
	even_line_cb                       :8 ,	//15:8
	even_line_y                        :8 ,	//23:16
	reserved01                         :7 ,	//reserved
	even_line_pat_en                   :1 ;	//31
}PE_M19_VCP_WCP_S_LINE_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c5dcL VCP_WCP_S_LINE_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_line_cr                        :8 ,	//7:0
	odd_line_cb                        :8 ,	//15:8
	odd_line_y                         :8 ,	//23:16
	reserved01                         :7 ,	//reserved
	odd_line_pat_en                    :1 ;	//31
}PE_M19_VCP_WCP_S_LINE_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e0L VCP_WCP_M_REC0_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec0_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec0_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec0_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC0_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e4L VCP_WCP_M_REC0_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec0_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec0_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec0_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC0_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e8L VCP_WCP_M_REC1_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec1_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec1_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec1_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC1_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c5ecL VCP_WCP_M_REC1_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec1_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec1_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec1_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC1_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f0L VCP_WCP_M_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :24,	//reserved
	compare_lr_diff_sel                :2 ,	//25:24
	compare_lr_sync_sel                :1 ,	//26
	compare_lr_mark_org_nac            :1 ,	//27
	reserved02                         :3 ,	//reserved
	compare_lr_en                      :1 ;	//31
}PE_M19_VCP_WCP_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f4L VCP_WCP_M_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	compare_lr_th_c                    :8 ,	//7:0
	compare_lr_th_y                    :8 ;	//15:8
}PE_M19_VCP_WCP_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f8L VCP_WCP_M_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_nac_cr                         :4 ,	//3:0
	clr_nac_cb                         :4 ,	//7:4
	clr_nac_y                          :8 ,	//15:8
	clr_bdr_cr                         :4 ,	//19:16
	clr_bdr_cb                         :4 ,	//23:20
	clr_bdr_y                          :8 ;	//31:24
}PE_M19_VCP_WCP_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c5fcL VCP_WCP_M_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w1_clr_dark_cr                     :4 ,	//3:0
	w1_clr_dark_cb                     :4 ,	//7:4
	w1_clr_dark_y                      :8 ,	//15:8
	w0_clr_dark_cr                     :4 ,	//19:16
	w0_clr_dark_cb                     :4 ,	//23:20
	w0_clr_dark_y                      :8 ;	//31:24
}PE_M19_VCP_WCP_M_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c604L VCP_WCP_M_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_imux_ctrl                   :3 ,	//2:0
	set_w0_dark_en                     :1 ,	//3 
	set_w1_imux_ctrl                   :3 ,	//6:4
	set_w1_dark_en                     :1 ,	//7 
	cg_disable                         :1 ,	//8 
	reserved01                         :7 ,	//reserved
	set_lparity_w0_imux_en             :1 ,	//16
	set_lparity_w0_imux                :1 ,	//17
	reserved02                         :2 ,	//reserved
	set_lparity_w1_imux_en             :1 ,	//20
	set_lparity_w1_imux                :1 ,	//21
	reserved03                         :2 ,	//reserved
	set_lparity_sync_c                 :3 ,	//26:24
	reserved04                         :1 ,	//reserved
	set_lparity_sync_y                 :3 ;	//30:28
}PE_M19_VCP_WCP_M_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c608L VCP_WCP_M_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_a0_c_imux_ctrl                 :3 ,	//2:0
	set_a0_c_constant_en               :1 ,	//3 
	set_a1_c_imux_ctrl                 :3 ,	//6:4
	set_a1_c_constant_en               :1 ,	//7 
	reserved01                         :8 ,	//reserved
	set_a0_y_imux_ctrl                 :3 ,	//18:16
	set_a0_y_constant_en               :1 ,	//19
	set_a1_y_imux_ctrl                 :3 ,	//22:20
	set_a1_y_constant_en               :1 ;	//23
}PE_M19_VCP_WCP_M_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c60cL VCP_WCP_M_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_abr_en                      :2 ,	//1:0
	set_w1_abr_en                      :2 ,	//3:2
	reserved01                         :4 ,	//reserved
	set_w0_awb_cr                      :1 ,	//8 
	set_w0_awb_cb                      :1 ,	//9 
	set_w0_awb_y                       :1 ,	//10
	reserved02                         :1 ,	//reserved
	set_w1_awb_cr                      :1 ,	//12
	set_w1_awb_cb                      :1 ,	//13
	set_w1_awb_y                       :1 ,	//14
	reserved03                         :8 ,	//reserved
	w1_clr_alpha_nac_en                :1 ,	//23
	w1_clr_alpha_nac                   :8 ;	//31:24
}PE_M19_VCP_WCP_M_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c610L VCP_WCP_M_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w0_clr_alpha                       :8 ,	//7:0
	w1_clr_alpha                       :8 ;	//15:8
}PE_M19_VCP_WCP_M_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c614L VCP_WCP_M_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_ha_o_mux_ctrl                  :4 ,	//3:0
	set_va_o_mux_ctrl                  :4 ,	//7:4
	set_de_o_mux_ctrl                  :4 ;	//11:8
}PE_M19_VCP_WCP_M_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c618L VCP_WCP_M_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_m_wcp           :4 ,	//3:0
	set_pic_start_y_mux_m_wcp          :4 ,	//7:4
	set_pic_init_c_mux_m_wcp           :4 ,	//11:8
	set_pic_start_c_mux_m_wcp          :4 ;	//15:12
}PE_M19_VCP_WCP_M_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900c628L VCP_WCP_S_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_nac_cr                         :4 ,	//3:0
	clr_nac_cb                         :4 ,	//7:4
	clr_nac_y                          :8 ,	//15:8
	clr_bdr_cr                         :4 ,	//19:16
	clr_bdr_cb                         :4 ,	//23:20
	clr_bdr_y                          :8 ;	//31:24
}PE_M19_VCP_WCP_S_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c62cL VCP_WCP_S_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	//reserved
	w0_clr_dark_cr                     :4 ,	//19:16
	w0_clr_dark_cb                     :4 ,	//23:20
	w0_clr_dark_y                      :8 ;	//31:24
}PE_M19_VCP_WCP_S_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c634L VCP_WCP_S_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_imux_ctrl                   :3 ,	//2:0
	set_w0_dark_en                     :1 ,	//3 
	reserved01                         :4 ,	//reserved
	cg_disable                         :1 ;	//8 
}PE_M19_VCP_WCP_S_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c63cL VCP_WCP_S_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_abr_en                      :2 ,	//1:0
	reserved01                         :6 ,	//reserved
	set_w0_awb_cr                      :1 ,	//8 
	set_w0_awb_cb                      :1 ,	//9 
	set_w0_awb_y                       :1 ;	//10
}PE_M19_VCP_WCP_S_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c640L VCP_WCP_S_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w0_clr_alpha                       :8 ;	//7:0
}PE_M19_VCP_WCP_S_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c644L VCP_WCP_S_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_ha_o_mux_ctrl                  :4 ,	//3:0
	set_va_o_mux_ctrl                  :4 ,	//7:4
	set_de_o_mux_ctrl                  :4 ;	//11:8
}PE_M19_VCP_WCP_S_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c648L VCP_WCP_S_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_s_wcp           :4 ,	//3:0
	set_pic_start_y_mux_s_wcp          :4 ,	//7:4
	set_pic_init_c_mux_s_wcp           :4 ,	//11:8
	set_pic_start_c_mux_s_wcp          :4 ;	//15:12
}PE_M19_VCP_WCP_S_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900c650L VCP_WCP_M_PIXEL_READ_DATA_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	//7:0
	msb8_rd_pel_cb                     :8 ,	//15:8
	msb8_rd_pel_y                      :8 ,	//23:16
	lsb2_rd_pel_cr                     :2 ,	//25:24
	lsb2_rd_pel_cb                     :2 ,	//27:26
	lsb2_rd_pel_y                      :2 ;	//29:28
}PE_M19_VCP_WCP_M_PIXEL_READ_DATA_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c654L VCP_WCP_M_PIXEL_READ_DATA_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	//7:0
	msb8_rd_pel_cb                     :8 ,	//15:8
	msb8_rd_pel_y                      :8 ,	//23:16
	lsb2_rd_pel_cr                     :2 ,	//25:24
	lsb2_rd_pel_cb                     :2 ,	//27:26
	lsb2_rd_pel_y                      :2 ;	//29:28
}PE_M19_VCP_WCP_M_PIXEL_READ_DATA_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c658L VCP_WCP_M_PIXEL_READ_DATA_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	//7:0
	msb8_rd_pel_cb                     :8 ,	//15:8
	msb8_rd_pel_y                      :8 ,	//23:16
	lsb2_rd_pel_cr                     :2 ,	//25:24
	lsb2_rd_pel_cb                     :2 ,	//27:26
	lsb2_rd_pel_y                      :2 ;	//29:28
}PE_M19_VCP_WCP_M_PIXEL_READ_DATA_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c65cL VCP_WCP_M_PIXEL_READ_DATA_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	//7:0
	msb8_rd_pel_cb                     :8 ,	//15:8
	msb8_rd_pel_y                      :8 ,	//23:16
	lsb2_rd_pel_cr                     :2 ,	//25:24
	lsb2_rd_pel_cb                     :2 ,	//27:26
	lsb2_rd_pel_y                      :2 ;	//29:28
}PE_M19_VCP_WCP_M_PIXEL_READ_DATA_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c660L VCP_SG_BDR_V0_PARAM_POS_M                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0_auto                    :13;	//28:16
}PE_M19_VCP_SG_BDR_V0_PARAM_POS_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c664L VCP_SG_BDR_V0_PARAM_SIZE_M                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_size_y_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_size_x_auto                    :13,	//28:16
	reserved02                         :1 ,	//reserved
	win_enable_4ch_auto                :1 ,	//30
	win_enable_auto                    :1 ;	//31
}PE_M19_VCP_SG_BDR_V0_PARAM_SIZE_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c668L VCP_SG_BDR_V1_PARAM_POS_M                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0_auto                    :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_PARAM_POS_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c66cL VCP_SG_BDR_V1_PARAM_SIZE_M                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_size_y_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_size_x_auto                    :13,	//28:16
	reserved02                         :1 ,	//reserved
	win_enable_4ch_auto                :1 ,	//30
	win_enable_auto                    :1 ;	//31
}PE_M19_VCP_SG_BDR_V1_PARAM_SIZE_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c670L VCP_SG_BDR_V1_PARAM_POS_S                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0_auto                    :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_PARAM_POS_S_T;
/*-----------------------------------------------------------------------------
                             0xc900c674L VCP_SG_BDR_V1_PARAM_SIZE_S                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_size_y_auto                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_size_x_auto                    :13,	//28:16
	reserved02                         :1 ,	//reserved
	win_enable_4ch_auto                :1 ,	//30
	win_enable_auto                    :1 ;	//31
}PE_M19_VCP_SG_BDR_V1_PARAM_SIZE_S_T;
/*-----------------------------------------------------------------------------
                             0xc900c680L VCP_SG_BDR_V0_0_M_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V0_0_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c684L VCP_SG_BDR_V0_0_M_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V0_0_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c688L VCP_SG_BDR_V0_0_M_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V0_0_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c690L VCP_SG_BDR_V0_1_M_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V0_1_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c694L VCP_SG_BDR_V0_1_M_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V0_1_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c698L VCP_SG_BDR_V0_1_M_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V0_1_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c0L VCP_SG_BDR_V1_0_M_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_0_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c4L VCP_SG_BDR_V1_0_M_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_0_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c8L VCP_SG_BDR_V1_0_M_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V1_0_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d0L VCP_SG_BDR_V1_1_M_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_1_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d4L VCP_SG_BDR_V1_1_M_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_1_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d8L VCP_SG_BDR_V1_1_M_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V1_1_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c720L VCP_SG_BDR_V1_0_S_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_0_S_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c724L VCP_SG_BDR_V1_0_S_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_0_S_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c728L VCP_SG_BDR_V1_0_S_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V1_0_S_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c730L VCP_SG_BDR_V1_1_S_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x0                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_1_S_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c734L VCP_SG_BDR_V1_1_S_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :13,	//12:0
	reserved01                         :3 ,	//reserved
	win_pos_x1                         :13;	//28:16
}PE_M19_VCP_SG_BDR_V1_1_S_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c738L VCP_SG_BDR_V1_1_S_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	//0 
	sync_ha_sub_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	num_ch                             :2 ,	//5:4
	reserved02                         :10,	//reserved
	win_border_width_right             :4 ,	//19:16
	win_border_width_left              :4 ,	//23:20
	win_border_width_down              :4 ,	//27:24
	win_border_width_up                :4 ;	//31:28
}PE_M19_VCP_SG_BDR_V1_1_S_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c760L VCP_WCP_M0_LRDIFF_CNT_YY_O                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_WCP_M0_LRDIFF_CNT_YY_O_T;
/*-----------------------------------------------------------------------------
                             0xc900c764L VCP_WCP_M1_LRDIFF_CNT_YY_O                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_WCP_M1_LRDIFF_CNT_YY_O_T;
/*-----------------------------------------------------------------------------
                             0xc900c770L VCP_WCP_M0_LRDIFF_CNT_CC_O                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_WCP_M0_LRDIFF_CNT_CC_O_T;
/*-----------------------------------------------------------------------------
                             0xc900c774L VCP_WCP_M1_LRDIFF_CNT_CC_O                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_WCP_M1_LRDIFF_CNT_CC_O_T;
/*-----------------------------------------------------------------------------
                             0xc900c780L VCP_WCP_M_REC5_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec5_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec5_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec5_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC5_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c784L VCP_WCP_M_REC5_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec5_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec5_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec5_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC5_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c788L VCP_WCP_M_REC5_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC5_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c78cL VCP_WCP_M_REC6_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec6_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec6_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec6_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC6_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c790L VCP_WCP_M_REC6_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec6_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec6_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec6_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC6_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c794L VCP_WCP_M_REC6_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC6_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c798L VCP_WCP_M_REC7_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec7_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec7_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec7_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC7_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c79cL VCP_WCP_M_REC7_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec7_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec7_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec7_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC7_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a0L VCP_WCP_M_REC7_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC7_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a4L VCP_WCP_M_REC8_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec8_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec8_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec8_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC8_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a8L VCP_WCP_M_REC8_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec8_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec8_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec8_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC8_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7acL VCP_WCP_M_REC8_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC8_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b0L VCP_WCP_M_REC9_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec9_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec9_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec9_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC9_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b4L VCP_WCP_M_REC9_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec9_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec9_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec9_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC9_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b8L VCP_WCP_M_REC9_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC9_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7c4L VCP_WCP_MS_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_ms_wcp          :4 ,	//3:0
	set_pic_start_y_mux_ms_wcp         :4 ,	//7:4
	set_pic_init_c_mux_ms_wcp          :4 ,	//11:8
	set_pic_start_c_mux_ms_wcp         :4 ;	//15:12
}PE_M19_VCP_WCP_MS_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900c800L VCP_WCP_ALPHA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	//reserved
	set_region_m_y_sync_sel            :2 ,	//5:4
	set_region_m_c_sync_sel            :2 ;	//7:6
}PE_M19_VCP_WCP_ALPHA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c804L VCP_WCP_ALPHA_GEN_Y_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_vsize                          :16,	//15:0
	set_hsize                          :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_Y_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c808L VCP_WCP_ALPHA_GEN_Y_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	region_shape                       :2 ,	//1:0
	alpha_inversion_y                  :1 ,	//2 
	rm_op_mode                         :2 ,	//4:3
	rm_enable                          :1 ,	//5 
	ellipse_ez_set                     :1 ,	//6 
	rm_yc_same_align                   :1 ,	//7 
	reserved01                         :8 ,	//reserved
	alpha_1                            :8 ,	//23:16
	alpha_0                            :8 ;	//31:24
}PE_M19_VCP_WCP_ALPHA_GEN_Y_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c80cL VCP_WCP_ALPHA_GEN_Y_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_a_q                             :16,	//15:0
	x0_p                               :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_Y_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c810L VCP_WCP_ALPHA_GEN_Y_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1_y1_tx_pp;	//31:0
}PE_M19_VCP_WCP_ALPHA_GEN_Y_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c814L VCP_WCP_ALPHA_GEN_Y_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	b_c_qq;	//31:0
}PE_M19_VCP_WCP_ALPHA_GEN_Y_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c818L VCP_WCP_ALPHA_GEN_Y_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dy                                 :16,	//15:0
	dx                                 :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_Y_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c81cL VCP_WCP_ALPHA_GEN_C_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_vsize                          :16,	//15:0
	set_hsize                          :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_C_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c820L VCP_WCP_ALPHA_GEN_C_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	region_shape                       :2 ,	//1:0
	alpha_inversion_c                  :1 ,	//2 
	eo_mode_en                         :1 ,	//3 
	reserved01                         :12,	//reserved
	alpha_1                            :8 ,	//23:16
	alpha_0                            :8 ;	//31:24
}PE_M19_VCP_WCP_ALPHA_GEN_C_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c824L VCP_WCP_ALPHA_GEN_C_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_a_q                             :16,	//15:0
	x0_p                               :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_C_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c828L VCP_WCP_ALPHA_GEN_C_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1_y1_tx_pp;	//31:0
}PE_M19_VCP_WCP_ALPHA_GEN_C_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c82cL VCP_WCP_ALPHA_GEN_C_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	b_c_qq;	//31:0
}PE_M19_VCP_WCP_ALPHA_GEN_C_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c830L VCP_WCP_ALPHA_GEN_C_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dy                                 :16,	//15:0
	dx                                 :16;	//31:16
}PE_M19_VCP_WCP_ALPHA_GEN_C_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c834L VCP_WCP_M_REC2_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec2_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec2_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec2_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC2_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c838L VCP_WCP_M_REC2_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec2_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec2_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec2_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC2_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c83cL VCP_WCP_M_REC3_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec3_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec3_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec3_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC3_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c840L VCP_WCP_M_REC3_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec3_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec3_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec3_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC3_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c844L VCP_WCP_M_REC4_POS_X                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec4_e_pos_x                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec4_s_pos_x                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec4_en                            :1 ;	//31
}PE_M19_VCP_WCP_M_REC4_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c848L VCP_WCP_M_REC4_POS_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec4_e_pos_y                       :13,	//12:0
	reserved01                         :3 ,	//reserved
	rec4_s_pos_y                       :13,	//28:16
	reserved02                         :2 ,	//reserved
	rec4_fill_en                       :1 ;	//31
}PE_M19_VCP_WCP_M_REC4_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c84cL VCP_WCP_M_REC0_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC0_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c850L VCP_WCP_M_REC1_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC1_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c854L VCP_WCP_M_REC2_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC2_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c858L VCP_WCP_M_REC3_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC3_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c85cL VCP_WCP_M_REC4_CLR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	//7:0
	clr_cb                             :8 ,	//15:8
	clr_y                              :8 ;	//23:16
}PE_M19_VCP_WCP_M_REC4_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c860L VCP_VSP_U0_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	reserved01                         :3 ,	//reserved
	cg_disable                         :1 ,	//4 
	reserved02                         :3 ,	//reserved
	center_position                    :8 ,	//15:8
	contrast                           :10;	//25:16
}PE_M19_VCP_VSP_U0_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900c864L VCP_VSP_U0_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	//reserved
	saturation                         :8 ,	//15:8
	brightness                         :10;	//25:16
}PE_M19_VCP_VSP_U0_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900c868L VCP_VSP_U1_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	reserved01                         :7 ,	//reserved
	center_position                    :8 ,	//15:8
	contrast                           :10;	//25:16
}PE_M19_VCP_VSP_U1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900c86cL VCP_VSP_U1_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	//reserved
	saturation                         :8 ,	//15:8
	brightness                         :10;	//25:16
}PE_M19_VCP_VSP_U1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900c870L VCP_CRC_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	crc_enable                         :1 ,	//0 
	crc_reset                          :1 ,	//1 
	reserved01                         :1 ,	//reserved
	auto_reset_disable                 :1 ,	//3 
	vs_level                           :1 ,	//4 
	hs_level                           :1 ,	//5 
	vs_mask                            :1 ,	//6 
	hs_mask                            :1 ;	//7 
}PE_M19_VCP_CRC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c874L VCP_CRC_DATA_MASK0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_DATA_MASK0_T;
/*-----------------------------------------------------------------------------
                             0xc900c878L VCP_CRC_DATA_MASK1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_DATA_MASK1_T;
/*-----------------------------------------------------------------------------
                             0xc900c87cL VCP_CRC_DATA_MASK2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_DATA_MASK2_T;
/*-----------------------------------------------------------------------------
                             0xc900c880L VCP_CRC_DATA_MASK3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_DATA_MASK3_T;
/*-----------------------------------------------------------------------------
                             0xc900c884L VCP_CRC_OUT0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_OUT0_T;
/*-----------------------------------------------------------------------------
                             0xc900c888L VCP_CRC_OUT1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_OUT1_T;
/*-----------------------------------------------------------------------------
                             0xc900c88cL VCP_CRC_OUT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_OUT2_T;
/*-----------------------------------------------------------------------------
                             0xc900c890L VCP_CRC_OUT3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	//0:31
}PE_M19_VCP_CRC_OUT3_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a0L VCP_SG_MVY_CTRL_A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	//15:0
	v_cnt                              :16;	//31:16
}PE_M19_VCP_SG_MVY_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a4L VCP_SG_MVC_CTRL_A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	//15:0
	v_cnt                              :16;	//31:16
}PE_M19_VCP_SG_MVC_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a8L VCP_SG_SVY_CTRL_A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	//15:0
	v_cnt                              :16;	//31:16
}PE_M19_VCP_SG_SVY_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8acL VCP_SG_SVC_CTRL_A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	//15:0
	v_cnt                              :16;	//31:16
}PE_M19_VCP_SG_SVC_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c900L VCP_DISP_INTR_MASK                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_mask           :1 ,	//0 
	vcp_mv_y_disp_intr1_mask           :1 ,	//1 
	vcp_mv_y_w0_intr_mask              :1 ,	//2 
	vcp_mv_y_w1_intr_mask              :1 ,	//3 
	reserved01                         :2 ,	//reserved
	vcp_sv_y_disp_intr0_mask           :1 ,	//6 
	vcp_sv_y_disp_intr1_mask           :1 ,	//7 
	vcp_sv_y_w0_intr_mask              :1 ,	//8 
	reserved02                         :3 ,	//reserved
	vcp_ms_y_disp_intr_mask            :1 ,	//12
	reserved03                         :3 ,	//reserved
	vcp_mv_c_disp_intr0_mask           :1 ,	//16
	vcp_mv_c_disp_intr1_mask           :1 ,	//17
	vcp_mv_c_w0_intr_mask              :1 ,	//18
	vcp_mv_c_w1_intr_mask              :1 ,	//19
	reserved04                         :2 ,	//reserved
	vcp_sv_c_disp_intr0_mask           :1 ,	//22
	vcp_sv_c_disp_intr1_mask           :1 ,	//23
	vcp_sv_c_w0_intr_mask              :1 ;	//24
}PE_M19_VCP_DISP_INTR_MASK_T;
/*-----------------------------------------------------------------------------
                             0xc900c904L VCP_DISP_INTR_CLEAR                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_clear          :1 ,	//0 
	vcp_mv_y_disp_intr1_clear          :1 ,	//1 
	vcp_mv_y_w0_intr_clear             :1 ,	//2 
	vcp_mv_y_w1_intr_clear             :1 ,	//3 
	reserved01                         :2 ,	//reserved
	vcp_sv_y_disp_intr0_clear          :1 ,	//6 
	vcp_sv_y_disp_intr1_clear          :1 ,	//7 
	vcp_sv_y_w0_intr_clear             :1 ,	//8 
	reserved02                         :3 ,	//reserved
	vcp_ms_y_disp_intr_clear           :1 ,	//12
	reserved03                         :3 ,	//reserved
	vcp_mv_c_disp_intr0_clear          :1 ,	//16
	vcp_mv_c_disp_intr1_clear          :1 ,	//17
	vcp_mv_c_w0_intr_clear             :1 ,	//18
	vcp_mv_c_w1_intr_clear             :1 ,	//19
	reserved04                         :2 ,	//reserved
	vcp_sv_c_disp_intr0_clear          :1 ,	//22
	vcp_sv_c_disp_intr1_clear          :1 ,	//23
	vcp_sv_c_w0_intr_clear             :1 ;	//24
}PE_M19_VCP_DISP_INTR_CLEAR_T;
/*-----------------------------------------------------------------------------
                             0xc900c908L VCP_DISP_INTR_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_status         :1 ,	//0 
	vcp_mv_y_disp_intr1_status         :1 ,	//1 
	vcp_mv_y_w0_intr_status            :1 ,	//2 
	vcp_mv_y_w1_intr_status            :1 ,	//3 
	reserved01                         :2 ,	//reserved
	vcp_sv_y_disp_intr0_status         :1 ,	//6 
	vcp_sv_y_disp_intr1_status         :1 ,	//7 
	vcp_sv_y_w0_intr_status            :1 ,	//8 
	reserved02                         :3 ,	//reserved
	vcp_ms_y_disp_intr_status          :1 ,	//12
	reserved03                         :3 ,	//reserved
	vcp_mv_c_disp_intr0_status         :1 ,	//16
	vcp_mv_c_disp_intr1_status         :1 ,	//17
	vcp_mv_c_w0_intr_status            :1 ,	//18
	vcp_mv_c_w1_intr_status            :1 ,	//19
	reserved04                         :2 ,	//reserved
	vcp_sv_c_disp_intr0_status         :1 ,	//22
	vcp_sv_c_disp_intr1_status         :1 ,	//23
	vcp_sv_c_w0_intr_status            :1 ;	//24
}PE_M19_VCP_DISP_INTR_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c90cL VCP_DISP_INTR0_POS_MV_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr0_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_mv_disp_intr0_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR0_POS_MV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c910L VCP_DISP_INTR1_POS_MV_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr1_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_mv_disp_intr1_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR1_POS_MV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c914L VCP_DISP_INTR0_POS_MV_C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr0_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_mv_disp_intr0_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR0_POS_MV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c918L VCP_DISP_INTR1_POS_MV_C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr1_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_mv_disp_intr1_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR1_POS_MV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c91cL VCP_DISP_INTR0_POS_SV_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr0_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_sv_disp_intr0_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR0_POS_SV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c920L VCP_DISP_INTR1_POS_SV_Y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr1_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_sv_disp_intr1_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR1_POS_SV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c924L VCP_DISP_INTR0_POS_SV_C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr0_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_sv_disp_intr0_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR0_POS_SV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c928L VCP_DISP_INTR1_POS_SV_C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr1_pos_x            :13,	//12:0
	reserved01                         :3 ,	//reserved
	vcp_sv_disp_intr1_pos_y            :13;	//28:16
}PE_M19_VCP_DISP_INTR1_POS_SV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c92cL VCP_DISP_INTR_SRC_SEL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_intr_mv_y_v_src                :1 ,	//0 
	vcp_intr_mv_y_h_src                :1 ,	//1 
	reserved01                         :1 ,	//reserved
	vcp_intr_mv_y_enable               :1 ,	//3 
	vcp_intr_mv_c_v_src                :1 ,	//4 
	vcp_intr_mv_c_h_src                :1 ,	//5 
	reserved02                         :1 ,	//reserved
	vcp_intr_mv_c_enable               :1 ,	//7 
	vcp_intr_sv_y_v_src                :1 ,	//8 
	vcp_intr_sv_y_h_src                :1 ,	//9 
	reserved03                         :1 ,	//reserved
	vcp_intr_sv_y_enable               :1 ,	//11
	vcp_intr_sv_c_v_src                :1 ,	//12
	vcp_intr_sv_c_h_src                :1 ,	//13
	reserved04                         :1 ,	//reserved
	vcp_intr_sv_c_enable               :1 ;	//15
}PE_M19_VCP_DISP_INTR_SRC_SEL_T;


typedef struct
{ 
	PE_M19_VCP_DISP_CTRL0_T                           vcp_disp_ctrl0;	//0x0400
	PE_M19_VCP_DISP_CTRL1_T                           vcp_disp_ctrl1;	//0x0404
	PE_M19_VCP_DISP_CTRL2_T                           vcp_disp_ctrl2;	//0x0408
	PE_M19_VCP_DISP_CTRL3_T                           vcp_disp_ctrl3;	//0x040C
	PE_M19_VCP_CDC_MV_SYNC_CTRL_T                     vcp_cdc_mv_sync_ctrl;	//0x0410
	PE_M19_VCP_CDC_MV_RST_CTRL_T                      vcp_cdc_mv_rst_ctrl;	//0x0414
	UINT32                                            reserved00[2];	//0x0418-0x041C
	PE_M19_VCP_U0_WIN_O_POS_T                         vcp_u0_win_o_pos;	//0x0420
	PE_M19_VCP_U0_WIN_O_SIZE_T                        vcp_u0_win_o_size;	//0x0424
	PE_M19_VCP_U0_PG_PAT_CTRL_T                       vcp_u0_pg_pat_ctrl;	//0x0428
	PE_M19_VCP_U0_PG_PEAK_SIZE_T                      vcp_u0_pg_peak_size;	//0x042C
	PE_M19_VCP_U0_CDC_Y_CTRL0_T                       vcp_u0_cdc_y_ctrl0;	//0x0430
	PE_M19_VCP_U0_CDC_Y_CTRL1_T                       vcp_u0_cdc_y_ctrl1;	//0x0434
	PE_M19_VCP_U0_CDC_Y_CTRL2_T                       vcp_u0_cdc_y_ctrl2;	//0x0438
	PE_M19_VCP_U0_CDC_Y_STATUS_T                      vcp_u0_cdc_y_status;	//0x043C
	PE_M19_VCP_U0_CDC_C_CTRL0_T                       vcp_u0_cdc_c_ctrl0;	//0x0440
	PE_M19_VCP_U0_CDC_C_CTRL1_T                       vcp_u0_cdc_c_ctrl1;	//0x0444
	PE_M19_VCP_U0_CDC_C_CTRL2_T                       vcp_u0_cdc_c_ctrl2;	//0x0448
	PE_M19_VCP_U0_CDC_C_STATUS_T                      vcp_u0_cdc_c_status;	//0x044C
	PE_M19_VCP_U1_WIN_O_POS_T                         vcp_u1_win_o_pos;	//0x0450
	PE_M19_VCP_U1_WIN_O_SIZE_T                        vcp_u1_win_o_size;	//0x0454
	PE_M19_VCP_U1_PG_PAT_CTRL_T                       vcp_u1_pg_pat_ctrl;	//0x0458
	PE_M19_VCP_U1_PG_PEAK_SIZE_T                      vcp_u1_pg_peak_size;	//0x045C
	PE_M19_VCP_U1_CDC_Y_CTRL0_T                       vcp_u1_cdc_y_ctrl0;	//0x0460
	PE_M19_VCP_U1_CDC_Y_CTRL1_T                       vcp_u1_cdc_y_ctrl1;	//0x0464
	PE_M19_VCP_U1_CDC_Y_CTRL2_T                       vcp_u1_cdc_y_ctrl2;	//0x0468
	PE_M19_VCP_U1_CDC_Y_STATUS_T                      vcp_u1_cdc_y_status;	//0x046C
	PE_M19_VCP_U1_CDC_C_CTRL0_T                       vcp_u1_cdc_c_ctrl0;	//0x0470
	PE_M19_VCP_U1_CDC_C_CTRL1_T                       vcp_u1_cdc_c_ctrl1;	//0x0474
	PE_M19_VCP_U1_CDC_C_CTRL2_T                       vcp_u1_cdc_c_ctrl2;	//0x0478
	PE_M19_VCP_U1_CDC_C_STATUS_T                      vcp_u1_cdc_c_status;	//0x047C
	PE_M19_VCP_U0_WIN_O_POS_AUX_T                     vcp_u0_win_o_pos_aux;	//0x0480
	PE_M19_VCP_U0_WIN_O_SIZE_AUX_T                    vcp_u0_win_o_size_aux;	//0x0484
	PE_M19_VCP_U1_WIN_O_POS_AUX_T                     vcp_u1_win_o_pos_aux;	//0x0488
	PE_M19_VCP_U1_WIN_O_SIZE_AUX_T                    vcp_u1_win_o_size_aux;	//0x048C
	UINT32                                            reserved01[20];	//0x0490-0x04DC
	PE_M19_VCP_SG_MVY_CTRL_0_T                        vcp_sg_mvy_ctrl_0;	//0x04E0
	PE_M19_VCP_SG_MVY_CTRL_1_T                        vcp_sg_mvy_ctrl_1;	//0x04E4
	PE_M19_VCP_SG_MVY_CTRL_2_T                        vcp_sg_mvy_ctrl_2;	//0x04E8
	PE_M19_VCP_SG_MVY_CTRL_3_T                        vcp_sg_mvy_ctrl_3;	//0x04EC
	PE_M19_VCP_SG_MVY_CTRL_4_T                        vcp_sg_mvy_ctrl_4;	//0x04F0
	PE_M19_VCP_SG_MVY_CTRL_5_T                        vcp_sg_mvy_ctrl_5;	//0x04F4
	PE_M19_VCP_SG_MVY_CTRL_6_T                        vcp_sg_mvy_ctrl_6;	//0x04F8
	PE_M19_VCP_SG_MVY_CTRL_7_T                        vcp_sg_mvy_ctrl_7;	//0x04FC
	PE_M19_VCP_SG_MVY_CTRL_8_T                        vcp_sg_mvy_ctrl_8;	//0x0500
	PE_M19_VCP_SG_MVY_CTRL_9_T                        vcp_sg_mvy_ctrl_9;	//0x0504
	UINT32                                            reserved02[2];	//0x0508-0x050C
	PE_M19_VCP_SG_MVC_CTRL_0_T                        vcp_sg_mvc_ctrl_0;	//0x0510
	PE_M19_VCP_SG_MVC_CTRL_1_T                        vcp_sg_mvc_ctrl_1;	//0x0514
	PE_M19_VCP_SG_MVC_CTRL_2_T                        vcp_sg_mvc_ctrl_2;	//0x0518
	PE_M19_VCP_SG_MVC_CTRL_3_T                        vcp_sg_mvc_ctrl_3;	//0x051C
	PE_M19_VCP_SG_MVC_CTRL_4_T                        vcp_sg_mvc_ctrl_4;	//0x0520
	PE_M19_VCP_SG_MVC_CTRL_5_T                        vcp_sg_mvc_ctrl_5;	//0x0524
	PE_M19_VCP_SG_MVC_CTRL_6_T                        vcp_sg_mvc_ctrl_6;	//0x0528
	PE_M19_VCP_SG_MVC_CTRL_7_T                        vcp_sg_mvc_ctrl_7;	//0x052C
	PE_M19_VCP_SG_MVC_CTRL_8_T                        vcp_sg_mvc_ctrl_8;	//0x0530
	PE_M19_VCP_SG_MVC_CTRL_9_T                        vcp_sg_mvc_ctrl_9;	//0x0534
	PE_M19_MON_VCP_U0Y_PIC_INIT_POS_T                 mon_vcp_u0y_pic_init_pos;	//0x0538
	PE_M19_MON_VCP_U0Y_PIC_START_POS_T                mon_vcp_u0y_pic_start_pos;	//0x053C
	PE_M19_MON_VCP_U0C_PIC_INIT_POS_T                 mon_vcp_u0c_pic_init_pos;	//0x0540
	PE_M19_MON_VCP_U0C_PIC_START_POS_T                mon_vcp_u0c_pic_start_pos;	//0x0544
	PE_M19_MON_VCP_U1Y_PIC_INIT_POS_T                 mon_vcp_u1y_pic_init_pos;	//0x0548
	PE_M19_MON_VCP_U1Y_PIC_START_POS_T                mon_vcp_u1y_pic_start_pos;	//0x054C
	PE_M19_MON_VCP_U1C_PIC_INIT_POS_T                 mon_vcp_u1c_pic_init_pos;	//0x0550
	PE_M19_MON_VCP_U1C_PIC_START_POS_T                mon_vcp_u1c_pic_start_pos;	//0x0554
	UINT32                                            reserved03[2];	//0x0558-0x055C
	PE_M19_VCP_SG_SVY_CTRL_0_T                        vcp_sg_svy_ctrl_0;	//0x0560
	PE_M19_VCP_SG_SVY_CTRL_1_T                        vcp_sg_svy_ctrl_1;	//0x0564
	PE_M19_VCP_SG_SVY_CTRL_2_T                        vcp_sg_svy_ctrl_2;	//0x0568
	PE_M19_VCP_SG_SVY_CTRL_3_T                        vcp_sg_svy_ctrl_3;	//0x056C
	PE_M19_VCP_SG_SVY_CTRL_4_T                        vcp_sg_svy_ctrl_4;	//0x0570
	PE_M19_VCP_SG_SVY_CTRL_5_T                        vcp_sg_svy_ctrl_5;	//0x0574
	PE_M19_VCP_SG_SVY_CTRL_6_T                        vcp_sg_svy_ctrl_6;	//0x0578
	PE_M19_VCP_SG_SVY_CTRL_7_T                        vcp_sg_svy_ctrl_7;	//0x057C
	PE_M19_VCP_SG_SVY_CTRL_8_T                        vcp_sg_svy_ctrl_8;	//0x0580
	PE_M19_VCP_SG_SVY_CTRL_9_T                        vcp_sg_svy_ctrl_9;	//0x0584
	UINT32                                            reserved04[2];	//0x0588-0x058C
	PE_M19_VCP_SG_SVC_CTRL_0_T                        vcp_sg_svc_ctrl_0;	//0x0590
	PE_M19_VCP_SG_SVC_CTRL_1_T                        vcp_sg_svc_ctrl_1;	//0x0594
	PE_M19_VCP_SG_SVC_CTRL_2_T                        vcp_sg_svc_ctrl_2;	//0x0598
	PE_M19_VCP_SG_SVC_CTRL_3_T                        vcp_sg_svc_ctrl_3;	//0x059C
	PE_M19_VCP_SG_SVC_CTRL_4_T                        vcp_sg_svc_ctrl_4;	//0x05A0
	PE_M19_VCP_SG_SVC_CTRL_5_T                        vcp_sg_svc_ctrl_5;	//0x05A4
	PE_M19_VCP_SG_SVC_CTRL_6_T                        vcp_sg_svc_ctrl_6;	//0x05A8
	PE_M19_VCP_SG_SVC_CTRL_7_T                        vcp_sg_svc_ctrl_7;	//0x05AC
	PE_M19_VCP_SG_SVC_CTRL_8_T                        vcp_sg_svc_ctrl_8;	//0x05B0
	PE_M19_VCP_SG_SVC_CTRL_9_T                        vcp_sg_svc_ctrl_9;	//0x05B4
	PE_M19_VCP_WCP_M_DISP_SIZE_T                      vcp_wcp_m_disp_size;	//0x05B8
	PE_M19_VCP_WCP_M_PG_PAT_CTRL_T                    vcp_wcp_m_pg_pat_ctrl;	//0x05BC
	PE_M19_VCP_WCP_S_DISP_SIZE_T                      vcp_wcp_s_disp_size;	//0x05C0
	PE_M19_VCP_WCP_S_PG_PAT_CTRL_T                    vcp_wcp_s_pg_pat_ctrl;	//0x05C4
	PE_M19_VCP_WCP_M_PIXEL_READ_CTRL_T                vcp_wcp_m_pixel_read_ctrl;	//0x05C8
	PE_M19_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T            vcp_wcp_m_pixel_read_ctrl_aux;	//0x05CC
	PE_M19_VCP_WCP_M_LINE_CTRL0_T                     vcp_wcp_m_line_ctrl0;	//0x05D0
	PE_M19_VCP_WCP_M_LINE_CTRL1_T                     vcp_wcp_m_line_ctrl1;	//0x05D4
	PE_M19_VCP_WCP_S_LINE_CTRL0_T                     vcp_wcp_s_line_ctrl0;	//0x05D8
	PE_M19_VCP_WCP_S_LINE_CTRL1_T                     vcp_wcp_s_line_ctrl1;	//0x05DC
	PE_M19_VCP_WCP_M_REC0_POS_X_T                     vcp_wcp_m_rec0_pos_x;	//0x05E0
	PE_M19_VCP_WCP_M_REC0_POS_Y_T                     vcp_wcp_m_rec0_pos_y;	//0x05E4
	PE_M19_VCP_WCP_M_REC1_POS_X_T                     vcp_wcp_m_rec1_pos_x;	//0x05E8
	PE_M19_VCP_WCP_M_REC1_POS_Y_T                     vcp_wcp_m_rec1_pos_y;	//0x05EC
	PE_M19_VCP_WCP_M_CTRL_0_T                         vcp_wcp_m_ctrl_0;	//0x05F0
	PE_M19_VCP_WCP_M_CTRL_1_T                         vcp_wcp_m_ctrl_1;	//0x05F4
	PE_M19_VCP_WCP_M_CTRL_2_T                         vcp_wcp_m_ctrl_2;	//0x05F8
	PE_M19_VCP_WCP_M_CTRL_3_T                         vcp_wcp_m_ctrl_3;	//0x05FC
	UINT32                                            reserved05;	//0x0600-0x0600
	PE_M19_VCP_WCP_M_CTRL_5_T                         vcp_wcp_m_ctrl_5;	//0x0604
	PE_M19_VCP_WCP_M_CTRL_6_T                         vcp_wcp_m_ctrl_6;	//0x0608
	PE_M19_VCP_WCP_M_CTRL_7_T                         vcp_wcp_m_ctrl_7;	//0x060C
	PE_M19_VCP_WCP_M_CTRL_8_T                         vcp_wcp_m_ctrl_8;	//0x0610
	PE_M19_VCP_WCP_M_CTRL_9_T                         vcp_wcp_m_ctrl_9;	//0x0614
	PE_M19_VCP_WCP_M_CTRL_10_T                        vcp_wcp_m_ctrl_10;	//0x0618
	UINT32                                            reserved06[3];	//0x061C-0x0624
	PE_M19_VCP_WCP_S_CTRL_2_T                         vcp_wcp_s_ctrl_2;	//0x0628
	PE_M19_VCP_WCP_S_CTRL_3_T                         vcp_wcp_s_ctrl_3;	//0x062C
	UINT32                                            reserved07;	//0x0630-0x0630
	PE_M19_VCP_WCP_S_CTRL_5_T                         vcp_wcp_s_ctrl_5;	//0x0634
	UINT32                                            reserved08;	//0x0638-0x0638
	PE_M19_VCP_WCP_S_CTRL_7_T                         vcp_wcp_s_ctrl_7;	//0x063C
	PE_M19_VCP_WCP_S_CTRL_8_T                         vcp_wcp_s_ctrl_8;	//0x0640
	PE_M19_VCP_WCP_S_CTRL_9_T                         vcp_wcp_s_ctrl_9;	//0x0644
	PE_M19_VCP_WCP_S_CTRL_10_T                        vcp_wcp_s_ctrl_10;	//0x0648
	UINT32                                            reserved09;	//0x064C-0x064C
	PE_M19_VCP_WCP_M_PIXEL_READ_DATA_0_T              vcp_wcp_m_pixel_read_data_0;	//0x0650
	PE_M19_VCP_WCP_M_PIXEL_READ_DATA_1_T              vcp_wcp_m_pixel_read_data_1;	//0x0654
	PE_M19_VCP_WCP_M_PIXEL_READ_DATA_2_T              vcp_wcp_m_pixel_read_data_2;	//0x0658
	PE_M19_VCP_WCP_M_PIXEL_READ_DATA_3_T              vcp_wcp_m_pixel_read_data_3;	//0x065C
	PE_M19_VCP_SG_BDR_V0_PARAM_POS_M_T                vcp_sg_bdr_v0_param_pos_m;	//0x0660
	PE_M19_VCP_SG_BDR_V0_PARAM_SIZE_M_T               vcp_sg_bdr_v0_param_size_m;	//0x0664
	PE_M19_VCP_SG_BDR_V1_PARAM_POS_M_T                vcp_sg_bdr_v1_param_pos_m;	//0x0668
	PE_M19_VCP_SG_BDR_V1_PARAM_SIZE_M_T               vcp_sg_bdr_v1_param_size_m;	//0x066C
	PE_M19_VCP_SG_BDR_V1_PARAM_POS_S_T                vcp_sg_bdr_v1_param_pos_s;	//0x0670
	PE_M19_VCP_SG_BDR_V1_PARAM_SIZE_S_T               vcp_sg_bdr_v1_param_size_s;	//0x0674
	UINT32                                            reserved010[2];	//0x0678-0x067C
	PE_M19_VCP_SG_BDR_V0_0_M_CTRL_0_T                 vcp_sg_bdr_v0_0_m_ctrl_0;	//0x0680
	PE_M19_VCP_SG_BDR_V0_0_M_CTRL_1_T                 vcp_sg_bdr_v0_0_m_ctrl_1;	//0x0684
	PE_M19_VCP_SG_BDR_V0_0_M_CTRL_2_T                 vcp_sg_bdr_v0_0_m_ctrl_2;	//0x0688
	UINT32                                            reserved011;	//0x068C-0x068C
	PE_M19_VCP_SG_BDR_V0_1_M_CTRL_0_T                 vcp_sg_bdr_v0_1_m_ctrl_0;	//0x0690
	PE_M19_VCP_SG_BDR_V0_1_M_CTRL_1_T                 vcp_sg_bdr_v0_1_m_ctrl_1;	//0x0694
	PE_M19_VCP_SG_BDR_V0_1_M_CTRL_2_T                 vcp_sg_bdr_v0_1_m_ctrl_2;	//0x0698
	UINT32                                            reserved012[9];	//0x069C-0x06BC
	PE_M19_VCP_SG_BDR_V1_0_M_CTRL_0_T                 vcp_sg_bdr_v1_0_m_ctrl_0;	//0x06C0
	PE_M19_VCP_SG_BDR_V1_0_M_CTRL_1_T                 vcp_sg_bdr_v1_0_m_ctrl_1;	//0x06C4
	PE_M19_VCP_SG_BDR_V1_0_M_CTRL_2_T                 vcp_sg_bdr_v1_0_m_ctrl_2;	//0x06C8
	UINT32                                            reserved013;	//0x06CC-0x06CC
	PE_M19_VCP_SG_BDR_V1_1_M_CTRL_0_T                 vcp_sg_bdr_v1_1_m_ctrl_0;	//0x06D0
	PE_M19_VCP_SG_BDR_V1_1_M_CTRL_1_T                 vcp_sg_bdr_v1_1_m_ctrl_1;	//0x06D4
	PE_M19_VCP_SG_BDR_V1_1_M_CTRL_2_T                 vcp_sg_bdr_v1_1_m_ctrl_2;	//0x06D8
	UINT32                                            reserved014[17];	//0x06DC-0x071C
	PE_M19_VCP_SG_BDR_V1_0_S_CTRL_0_T                 vcp_sg_bdr_v1_0_s_ctrl_0;	//0x0720
	PE_M19_VCP_SG_BDR_V1_0_S_CTRL_1_T                 vcp_sg_bdr_v1_0_s_ctrl_1;	//0x0724
	PE_M19_VCP_SG_BDR_V1_0_S_CTRL_2_T                 vcp_sg_bdr_v1_0_s_ctrl_2;	//0x0728
	UINT32                                            reserved015;	//0x072C-0x072C
	PE_M19_VCP_SG_BDR_V1_1_S_CTRL_0_T                 vcp_sg_bdr_v1_1_s_ctrl_0;	//0x0730
	PE_M19_VCP_SG_BDR_V1_1_S_CTRL_1_T                 vcp_sg_bdr_v1_1_s_ctrl_1;	//0x0734
	PE_M19_VCP_SG_BDR_V1_1_S_CTRL_2_T                 vcp_sg_bdr_v1_1_s_ctrl_2;	//0x0738
	UINT32                                            reserved016[9];	//0x073C-0x075C
	PE_M19_VCP_WCP_M0_LRDIFF_CNT_YY_O_T               vcp_wcp_m0_lrdiff_cnt_yy_o;	//0x0760
	PE_M19_VCP_WCP_M1_LRDIFF_CNT_YY_O_T               vcp_wcp_m1_lrdiff_cnt_yy_o;	//0x0764
	UINT32                                            reserved017[2];	//0x0768-0x076C
	PE_M19_VCP_WCP_M0_LRDIFF_CNT_CC_O_T               vcp_wcp_m0_lrdiff_cnt_cc_o;	//0x0770
	PE_M19_VCP_WCP_M1_LRDIFF_CNT_CC_O_T               vcp_wcp_m1_lrdiff_cnt_cc_o;	//0x0774
	UINT32                                            reserved018[2];	//0x0778-0x077C
	PE_M19_VCP_WCP_M_REC5_POS_X_T                     vcp_wcp_m_rec5_pos_x;	//0x0780
	PE_M19_VCP_WCP_M_REC5_POS_Y_T                     vcp_wcp_m_rec5_pos_y;	//0x0784
	PE_M19_VCP_WCP_M_REC5_CLR_T                       vcp_wcp_m_rec5_clr;	//0x0788
	PE_M19_VCP_WCP_M_REC6_POS_X_T                     vcp_wcp_m_rec6_pos_x;	//0x078C
	PE_M19_VCP_WCP_M_REC6_POS_Y_T                     vcp_wcp_m_rec6_pos_y;	//0x0790
	PE_M19_VCP_WCP_M_REC6_CLR_T                       vcp_wcp_m_rec6_clr;	//0x0794
	PE_M19_VCP_WCP_M_REC7_POS_X_T                     vcp_wcp_m_rec7_pos_x;	//0x0798
	PE_M19_VCP_WCP_M_REC7_POS_Y_T                     vcp_wcp_m_rec7_pos_y;	//0x079C
	PE_M19_VCP_WCP_M_REC7_CLR_T                       vcp_wcp_m_rec7_clr;	//0x07A0
	PE_M19_VCP_WCP_M_REC8_POS_X_T                     vcp_wcp_m_rec8_pos_x;	//0x07A4
	PE_M19_VCP_WCP_M_REC8_POS_Y_T                     vcp_wcp_m_rec8_pos_y;	//0x07A8
	PE_M19_VCP_WCP_M_REC8_CLR_T                       vcp_wcp_m_rec8_clr;	//0x07AC
	PE_M19_VCP_WCP_M_REC9_POS_X_T                     vcp_wcp_m_rec9_pos_x;	//0x07B0
	PE_M19_VCP_WCP_M_REC9_POS_Y_T                     vcp_wcp_m_rec9_pos_y;	//0x07B4
	PE_M19_VCP_WCP_M_REC9_CLR_T                       vcp_wcp_m_rec9_clr;	//0x07B8
	UINT32                                            reserved019[2];	//0x07BC-0x07C0
	PE_M19_VCP_WCP_MS_CTRL_10_T                       vcp_wcp_ms_ctrl_10;	//0x07C4
	UINT32                                            reserved020;	//0x07C8-0x07C8
	UINT32                                            reserved243[13];	//0x7cc-0x7fc
	PE_M19_VCP_WCP_ALPHA_CTRL_T                       vcp_wcp_alpha_ctrl;	//0x0800
	PE_M19_VCP_WCP_ALPHA_GEN_Y_0_T                    vcp_wcp_alpha_gen_y_0;	//0x0804
	PE_M19_VCP_WCP_ALPHA_GEN_Y_1_T                    vcp_wcp_alpha_gen_y_1;	//0x0808
	PE_M19_VCP_WCP_ALPHA_GEN_Y_2_T                    vcp_wcp_alpha_gen_y_2;	//0x080C
	PE_M19_VCP_WCP_ALPHA_GEN_Y_3_T                    vcp_wcp_alpha_gen_y_3;	//0x0810
	PE_M19_VCP_WCP_ALPHA_GEN_Y_4_T                    vcp_wcp_alpha_gen_y_4;	//0x0814
	PE_M19_VCP_WCP_ALPHA_GEN_Y_5_T                    vcp_wcp_alpha_gen_y_5;	//0x0818
	PE_M19_VCP_WCP_ALPHA_GEN_C_0_T                    vcp_wcp_alpha_gen_c_0;	//0x081C
	PE_M19_VCP_WCP_ALPHA_GEN_C_1_T                    vcp_wcp_alpha_gen_c_1;	//0x0820
	PE_M19_VCP_WCP_ALPHA_GEN_C_2_T                    vcp_wcp_alpha_gen_c_2;	//0x0824
	PE_M19_VCP_WCP_ALPHA_GEN_C_3_T                    vcp_wcp_alpha_gen_c_3;	//0x0828
	PE_M19_VCP_WCP_ALPHA_GEN_C_4_T                    vcp_wcp_alpha_gen_c_4;	//0x082C
	PE_M19_VCP_WCP_ALPHA_GEN_C_5_T                    vcp_wcp_alpha_gen_c_5;	//0x0830
	PE_M19_VCP_WCP_M_REC2_POS_X_T                     vcp_wcp_m_rec2_pos_x;	//0x0834
	PE_M19_VCP_WCP_M_REC2_POS_Y_T                     vcp_wcp_m_rec2_pos_y;	//0x0838
	PE_M19_VCP_WCP_M_REC3_POS_X_T                     vcp_wcp_m_rec3_pos_x;	//0x083C
	PE_M19_VCP_WCP_M_REC3_POS_Y_T                     vcp_wcp_m_rec3_pos_y;	//0x0840
	PE_M19_VCP_WCP_M_REC4_POS_X_T                     vcp_wcp_m_rec4_pos_x;	//0x0844
	PE_M19_VCP_WCP_M_REC4_POS_Y_T                     vcp_wcp_m_rec4_pos_y;	//0x0848
	PE_M19_VCP_WCP_M_REC0_CLR_T                       vcp_wcp_m_rec0_clr;	//0x084C
	PE_M19_VCP_WCP_M_REC1_CLR_T                       vcp_wcp_m_rec1_clr;	//0x0850
	PE_M19_VCP_WCP_M_REC2_CLR_T                       vcp_wcp_m_rec2_clr;	//0x0854
	PE_M19_VCP_WCP_M_REC3_CLR_T                       vcp_wcp_m_rec3_clr;	//0x0858
	PE_M19_VCP_WCP_M_REC4_CLR_T                       vcp_wcp_m_rec4_clr;	//0x085C
	PE_M19_VCP_VSP_U0_CTRL_00_T                       vcp_vsp_u0_ctrl_00;	//0x0860
	PE_M19_VCP_VSP_U0_CTRL_01_T                       vcp_vsp_u0_ctrl_01;	//0x0864
	PE_M19_VCP_VSP_U1_CTRL_00_T                       vcp_vsp_u1_ctrl_00;	//0x0868
	PE_M19_VCP_VSP_U1_CTRL_01_T                       vcp_vsp_u1_ctrl_01;	//0x086C
	PE_M19_VCP_CRC_CTRL_T                             vcp_crc_ctrl;	//0x0870
	PE_M19_VCP_CRC_DATA_MASK0_T                       vcp_crc_data_mask0;	//0x0874
	PE_M19_VCP_CRC_DATA_MASK1_T                       vcp_crc_data_mask1;	//0x0878
	PE_M19_VCP_CRC_DATA_MASK2_T                       vcp_crc_data_mask2;	//0x087C
	PE_M19_VCP_CRC_DATA_MASK3_T                       vcp_crc_data_mask3;	//0x0880
	PE_M19_VCP_CRC_OUT0_T                             vcp_crc_out0;	//0x0884
	PE_M19_VCP_CRC_OUT1_T                             vcp_crc_out1;	//0x0888
	PE_M19_VCP_CRC_OUT2_T                             vcp_crc_out2;	//0x088C
	PE_M19_VCP_CRC_OUT3_T                             vcp_crc_out3;	//0x0890
	UINT32                                            reserved021[3];	//0x0894-0x089C
	PE_M19_VCP_SG_MVY_CTRL_A_T                        vcp_sg_mvy_ctrl_a;	//0x08A0
	PE_M19_VCP_SG_MVC_CTRL_A_T                        vcp_sg_mvc_ctrl_a;	//0x08A4
	PE_M19_VCP_SG_SVY_CTRL_A_T                        vcp_sg_svy_ctrl_a;	//0x08A8
	PE_M19_VCP_SG_SVC_CTRL_A_T                        vcp_sg_svc_ctrl_a;	//0x08AC
	UINT32                                            reserved022;	//0x08B0-0x08B0
	UINT32                                            reserved288[19];	//0x8b4-0x8fc
	PE_M19_VCP_DISP_INTR_MASK_T                       vcp_disp_intr_mask;	//0x0900
	PE_M19_VCP_DISP_INTR_CLEAR_T                      vcp_disp_intr_clear;	//0x0904
	PE_M19_VCP_DISP_INTR_STATUS_T                     vcp_disp_intr_status;	//0x0908
	PE_M19_VCP_DISP_INTR0_POS_MV_Y_T                  vcp_disp_intr0_pos_mv_y;	//0x090C
	PE_M19_VCP_DISP_INTR1_POS_MV_Y_T                  vcp_disp_intr1_pos_mv_y;	//0x0910
	PE_M19_VCP_DISP_INTR0_POS_MV_C_T                  vcp_disp_intr0_pos_mv_c;	//0x0914
	PE_M19_VCP_DISP_INTR1_POS_MV_C_T                  vcp_disp_intr1_pos_mv_c;	//0x0918
	PE_M19_VCP_DISP_INTR0_POS_SV_Y_T                  vcp_disp_intr0_pos_sv_y;	//0x091C
	PE_M19_VCP_DISP_INTR1_POS_SV_Y_T                  vcp_disp_intr1_pos_sv_y;	//0x0920
	PE_M19_VCP_DISP_INTR0_POS_SV_C_T                  vcp_disp_intr0_pos_sv_c;	//0x0924
	PE_M19_VCP_DISP_INTR1_POS_SV_C_T                  vcp_disp_intr1_pos_sv_c;	//0x0928
	PE_M19_VCP_DISP_INTR_SRC_SEL_T                    vcp_disp_intr_src_sel;	//0x092C
	UINT32                                            reserved023;	//0x0930-0x0930
}PE_VCP_DISP_REG_M19_T;
#endif