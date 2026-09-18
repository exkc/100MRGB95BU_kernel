#ifndef _PE_SRE_SHP_REG_M17C0_H_
#define _PE_SRE_SHP_REG_M17C0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9009000L shp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_detour                     :1 ,	// 4:4
	reg_top_bypass                     :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_cg_disable                 :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_ode_3d                     :1 ;	// 12:12
}PE_M17C0_SR_SHP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009004L shp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_M17C0_SR_SHP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009008L shp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_va_ris_cnt                 :16,	// 15:0
	reg_top_va_fal_cnt                 :16;	// 31:16
}PE_M17C0_SR_SHP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90090b0L shp_derh_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90090b4L shp_derh_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90090b8L shp_derh_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90090bcL shp_derh_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90090c0L shp_derh_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90090c4L shp_derh_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_csft_gain                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_th_gain_edge              :6 ,	// 21:16
	reg_derh_th_gain_flat              :2 ,	// 23:22
	reg_derh_th_manual_th              :7 ,	// 30:24
	reg_derh_th_manual_en              :1 ;	// 31:31
}PE_M17C0_SR_SHP_DERH_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90090c8L shp_derh_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_bflt_tap_size             :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_derh_amean_en                  :1 ,	// 24:24
	reserved04                         :1 ,	// reserved
	reg_derh_edge_filter_v_tap         :2 ,	// 27:26
	reserved05                         :3 ,	// reserved
	reg_derh_edge_y_filter_en          :1 ;	// 31:31
}PE_M17C0_SR_SHP_DERH_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90090ccL shp_derh_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_avg_filter_tap            :2 ,	// 1:0
	reserved01                         :22,	// reserved
	reg_derh_flat_filter_gain          :6 ,	// 29:24
	reg_derh_flat_filter_type          :1 ,	// 30:30
	reg_derh_flat_filter_en            :1 ;	// 31:31
}PE_M17C0_SR_SHP_DERH_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90090d0L shp_derh_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90090d4L shp_derh_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90090d8L shp_derh_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90090dcL shp_derh_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90090e0L shp_derh_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERH_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90090f0L shp_derv_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_en                        :1 ,	// 0:0
	reg_derv_w_sel                     :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_derv_bif_en                    :1 ,	// 3:3
	reg_derv_output_mux                :4 ,	// 7:4
	reg_derv_bif_manual_th             :8 ,	// 15:8
	reg_derv_th_gain                   :6 ,	// 21:16
	reserved02                         :2 ,	// reserved
	reg_derv_th_mode                   :1 ;	// 24:24
}PE_M17C0_SR_SHP_DERV_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90090f4L shp_derv_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_M17C0_SR_SHP_DERV_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90090f8L shp_derv_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_DERV_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90090fcL shp_derv_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_M17C0_SR_SHP_DERV_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9009110L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_M17C0_SR_SHP_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009114L shp_dp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_spc_gain_e_b                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_spc_gain_e_w                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_spc_gain_t_b                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_spc_gain_t_w                   :7 ;	// 30:24
}PE_M17C0_SR_SHP_DP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009118L shp_dp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptic_gain_e_b                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_ptic_gain_e_w                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_ptic_gain_t_b                  :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_ptic_gain_t_w                  :7 ;	// 30:24
}PE_M17C0_SR_SHP_DP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900911cL shp_dp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgenc_gain_e_b                 :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_tgenc_gain_e_w                 :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_tgenc_gain_t_b                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgenc_gain_t_w                 :7 ;	// 30:24
}PE_M17C0_SR_SHP_DP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009120L shp_dp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ;	// 15:8
}PE_M17C0_SR_SHP_DP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009124L shp_dp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_y0                         :8 ,	// 7:0
	reg_der_x0                         :8 ,	// 15:8
	reg_der_y1                         :8 ,	// 23:16
	reg_der_x1                         :8 ;	// 31:24
}PE_M17C0_SR_SHP_DP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009128L shp_dp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_y2                         :8 ,	// 7:0
	reg_der_x2                         :8 ,	// 15:8
	reg_der_y3                         :8 ,	// 23:16
	reg_der_x3                         :8 ;	// 31:24
}PE_M17C0_SR_SHP_DP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900912cL shp_dp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ;	// 7:0
}PE_M17C0_SR_SHP_DP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009130L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ,	// 0:0
	reserved01                         :11,	// reserved
	reg_sp_sobel_sel                   :2 ;	// 13:12
}PE_M17C0_SR_SHP_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009134L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ,	// 23:16
	reg_sp_im_gain_v                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009138L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_sobel_weight                :8 ,	// 7:0
	reg_sp_lap_weight                  :8 ,	// 15:8
	reg_sp_sobel_man_en                :1 ,	// 16:16
	reserved01                         :7 ,	// reserved
	reg_sp_sobel_man_gain              :8 ;	// 31:24
}PE_M17C0_SR_SHP_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900913cL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_M17C0_SR_SHP_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009140L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ,	// 11:8
	reg_sp_sobel_gx_manual_en          :1 ,	// 12:12
	reserved02                         :3 ,	// reserved
	reg_sp_sobel_gx_manual_gain        :8 ;	// 23:16
}PE_M17C0_SR_SHP_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009144L shp_sp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009148L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lap_h_mode                  :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_sp_lap_v_mode                  :3 ;	// 6:4
}PE_M17C0_SR_SHP_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900914cL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_sp_gb_x1                       :8 ,	// 15:8
	reg_sp_gb_y1                       :8 ;	// 23:16
}PE_M17C0_SR_SHP_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009150L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_M17C0_SR_SHP_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009154L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009158L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900915cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_M17C0_SR_SHP_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009160L shp_sp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_M17C0_SR_SHP_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009170L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ,	// 0:0
	reserved01                         :11,	// reserved
	reg_mp_sobel_sel                   :2 ;	// 13:12
}PE_M17C0_SR_SHP_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009174L shp_mp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_im_gain_h                   :8 ,	// 23:16
	reg_mp_im_gain_v                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009178L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_sobel_weight                :8 ,	// 7:0
	reg_mp_lap_weight                  :8 ,	// 15:8
	reg_mp_sobel_man_en                :1 ,	// 16:16
	reserved01                         :7 ,	// reserved
	reg_mp_sobel_man_gain              :8 ;	// 31:24
}PE_M17C0_SR_SHP_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900917cL shp_mp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_mp_lap_gain_v_7                :4 ,	// 7:4
	reg_mp_lap_gain_v_5                :4 ,	// 11:8
	reg_mp_lap_gain_v_3                :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	reg_mp_lap_gain_h_7                :4 ,	// 23:20
	reg_mp_lap_gain_h_5                :4 ,	// 27:24
	reg_mp_lap_gain_h_3                :4 ;	// 31:28
}PE_M17C0_SR_SHP_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009180L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ,	// 11:8
	reg_mp_sobel_gx_manual_en          :1 ,	// 12:12
	reserved02                         :3 ,	// reserved
	reg_mp_sobel_gx_manual_gain        :8 ,	// 23:16
	reg_mp_par_out_sel                 :3 ;	// 26:24
}PE_M17C0_SR_SHP_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009184L shp_mp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009188L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lap_h_mode                  :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_mp_lap_v_mode                  :3 ;	// 6:4
}PE_M17C0_SR_SHP_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900918cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_mp_gb_x1                       :8 ,	// 15:8
	reg_mp_gb_y1                       :8 ;	// 23:16
}PE_M17C0_SR_SHP_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009190L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_M17C0_SR_SHP_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009194L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009198L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_M17C0_SR_SHP_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900919cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_M17C0_SR_SHP_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90091a0L shp_mp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_M17C0_SR_SHP_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90091b0L shp_coring_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_map_h_size                :2 ,	// 1:0
	reg_fd_a_nomalize_en               :1 ,	// 2:2
	reg_fd_t_nomalize_en               :1 ,	// 3:3
	reg_fd_t_cut_resolution            :2 ,	// 5:4
	reserved01                         :2 ,	// reserved
	reg_fd_a_map_post_filter_en        :1 ,	// 8:8
	reg_fd_t_cross_check               :1 ,	// 9:9
	reserved02                         :6 ,	// reserved
	reg_fd_pre_a_map_h_size            :3 ,	// 18:16
	reg_fd_pre_a_map_v_size            :2 ,	// 20:19
	reg_fd_pre_a_cut_resolution        :3 ,	// 23:21
	reg_fd_cross_th                    :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90091b4L shp_coring_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90091b8L shp_coring_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90091bcL shp_coring_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90091c0L shp_coring_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90091c4L shp_coring_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90091c8L shp_coring_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90091ccL shp_coring_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90091d0L shp_coring_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mpc_coring_mode                :2 ,	// 1:0
	reg_spc_coring_mode                :2 ,	// 3:2
	reg_mpc_coring_en                  :1 ,	// 4:4
	reg_spc_coring_en                  :1 ,	// 5:5
	reg_ptic_coring_en                 :1 ,	// 6:6
	reg_ptic_coring_mode               :2 ,	// 8:7
	reg_tgenc_coring_en                :1 ,	// 9:9
	reg_tgenc_coring_mode              :2 ,	// 11:10
	reserved01                         :4 ,	// reserved
	reg_fd_mul_base_t                  :8 ,	// 23:16
	reg_fd_mul_base_e                  :8 ;	// 31:24
}PE_M17C0_SR_SHP_CORING_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90091d4L shp_coring_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mpc_gain_e_b                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mpc_gain_e_w                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mpc_gain_t_b                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_mpc_gain_t_w                   :7 ;	// 30:24
}PE_M17C0_SR_SHP_CORING_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009200L shp_pti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptiv_enable                    :1 ,	// 0:0
	reg_ptiv_debug_map_en              :1 ,	// 1:1
	reg_ptiv_mm_tap_size               :2 ,	// 3:2
	reg_ptiv_avg_tap_size              :2 ,	// 5:4
	reg_ptiv_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptiv_master_gain               :8 ;	// 15:8
}PE_M17C0_SR_SHP_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009204L shp_pti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptih_enable                    :1 ,	// 0:0
	reg_ptih_debug_map_en              :1 ,	// 1:1
	reg_ptih_mm_tap_size               :2 ,	// 3:2
	reg_ptih_avg_tap_size              :2 ,	// 5:4
	reg_ptih_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptih_master_gain               :8 ;	// 15:8
}PE_M17C0_SR_SHP_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009208L shp_sti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sti_enable                     :1 ,	// 0:0
	reg_sti_debug_map_en               :1 ,	// 1:1
	reg_sti_mm_tap_size                :2 ,	// 3:2
	reg_sti_avg_tap_size               :2 ,	// 5:4
	reg_sti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_sti_master_gain                :8 ,	// 15:8
	reg_sti_texture_gain               :8 ,	// 23:16
	reg_sti_edge_gain                  :8 ;	// 31:24
}PE_M17C0_SR_SHP_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900920cL shp_sti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_STI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009220L shp_dj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_edf_en                      :1 ,	// 0:0
	reg_dj_hv_filter_en                :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_dj_edge_adaptive_en            :1 ,	// 3:3
	reg_dj_line_variation_mode         :1 ,	// 4:4
	reg_dj_l_type_protection           :1 ,	// 5:5
	reserved02                         :1 ,	// reserved
	reg_dj_direction_type_mode         :1 ,	// 7:7
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_M17C0_SR_SHP_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009224L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_M17C0_SR_SHP_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009228L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_M17C0_SR_SHP_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900922cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_M17C0_SR_SHP_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009260L shp_sqm_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_outmux_debugmap_enable     :4 ,	// 3:0
	reg_sqm_iir                        :4 ,	// 7:4
	reg_sqm_i_score                    :8 ,	// 15:8
	reg_sqm_v_score                    :8 ,	// 23:16
	reg_sqm_l_score                    :8 ;	// 31:24
}PE_M17C0_SR_SHP_SQM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009264L shp_sqm_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_v_limit                    :8 ,	// 7:0
	reg_sqm_l_limit                    :8 ,	// 15:8
	reg_sqm_score_threshold            :8 ,	// 23:16
	reg_sqm_flat_threshold             :8 ;	// 31:24
}PE_M17C0_SR_SHP_SQM_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009268L shp_sqm_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pip_win_x0                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_sqm_pip_win_y0                 :11;	// 26:16
}PE_M17C0_SR_SHP_SQM_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900926cL shp_sqm_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pip_win_x1                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_sqm_pip_win_y1                 :11;	// 26:16
}PE_M17C0_SR_SHP_SQM_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009270L shp_sqm_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_charcter_delta_limit       :8 ,	// 7:0
	reg_sqm_boundary_width             :8 ,	// 15:8
	reg_sqm_video_height               :8 ;	// 23:16
}PE_M17C0_SR_SHP_SQM_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009274L shp_sqm_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pc_threshold               :8 ,	// 7:0
	reg_sqm_pc_delta_limit             :8 ,	// 15:8
	reg_sqm_pc_pixel_minimal_limit     :8 ;	// 23:16
}PE_M17C0_SR_SHP_SQM_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009280L shp_bbd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_en                         :1 ,	// 0:0
	reg_bbd_hys_mode                   :5 ,	// 5:1
	reg_bbd_op_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_bbd_cnt_th                     :8 ,	// 15:8
	reg_bbd_diff_th                    :8 ;	// 23:16
}PE_M17C0_SR_SHP_BBD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009284L shp_bbd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_x0                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_bbd_y0                         :12;	// 27:16
}PE_M17C0_SR_SHP_BBD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009288L shp_bbd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_x1                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_bbd_y1                         :12;	// 27:16
}PE_M17C0_SR_SHP_BBD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90092a0L shp_tgen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_on_off                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tgen_initial_seed_mode         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tgen_dbg_en                    :1 ,	// 8:8
	reserved03                         :7 ,	// reserved
	reg_tgen_table_sel                 :4 ,	// 19:16
	reserved04                         :4 ,	// reserved
	reg_tgen_master_gain               :8 ;	// 31:24
}PE_M17C0_SR_SHP_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90092a4L shp_tgen_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_delta_h_bound             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_delta_l_bound             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_delta_max                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_delta_scale               :3 ;	// 26:24
}PE_M17C0_SR_SHP_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90092a8L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_M17C0_SR_SHP_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90092acL shp_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_x0;	// 31:0
}PE_M17C0_SR_SHP_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90092b0L shp_tgen_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_dr_ratio                  :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_tgen_dr_th                     :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_tgen_mm_offset                 :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	reg_tgen_mm_sel_mode               :2 ;	// 25:24
}PE_M17C0_SR_SHP_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90092b4L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_lavg_th                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_M17C0_SR_SHP_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90092b8L shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_M17C0_SR_SHP_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90092bcL shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_M17C0_SR_SHP_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90092c0L shp_tgen_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_map_edge_gain             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_map_detail_gain           :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_map_offset                :8 ,	// 23:16
	reg_tgen_gs_noise                  :6 ;	// 29:24
}PE_M17C0_SR_SHP_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90092c4L shp_tgen_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_gain7                     :4 ,	// 3:0
	reg_tgen_gain6                     :4 ,	// 7:4
	reg_tgen_gain5                     :4 ,	// 11:8
	reg_tgen_gain4                     :4 ,	// 15:12
	reg_tgen_gain3                     :4 ,	// 19:16
	reg_tgen_gain2                     :4 ,	// 23:20
	reg_tgen_gain1                     :4 ,	// 27:24
	reg_tgen_gain0                     :4 ;	// 31:28
}PE_M17C0_SR_SHP_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90092c8L shp_contrast_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_shp_en                      :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_lc_gb_en                       :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lc_center_target               :8 ,	// 15:8
	reg_lc_center_gain                 :8 ,	// 23:16
	reg_lc_local_gain                  :8 ;	// 31:24
}PE_M17C0_SR_SHP_CONTRAST_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90092ccL shp_contrast_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_M17C0_SR_SHP_CONTRAST_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90092d0L shp_contrast_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_M17C0_SR_SHP_CONTRAST_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90092d4L shp_contrast_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gain_e_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lc_gain_e_w                    :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_lc_gain_t_b                    :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_lc_gain_t_w                    :7 ;	// 30:24
}PE_M17C0_SR_SHP_CONTRAST_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90092d8L shp_contrast_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_apl_iir_en                  :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_lc_coring_mode                 :2 ,	// 5:4
	reserved02                         :10,	// reserved
	reg_lc_apl_iir_gain                :8 ;	// 23:16
}PE_M17C0_SR_SHP_CONTRAST_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90092dcL shp_mnr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_M17C0_SR_SHP_MNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90092e0L shp_mnr_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reg_fd_mnr_s2_ratio_min            :8 ,	// 15:8
	reg_fd_mnr_s2_ratio_max            :8 ,	// 23:16
	reg_fd_mnr_s2_mmd_min              :8 ;	// 31:24
}PE_M17C0_SR_SHP_MNR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90092e4L shp_mnr_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_gain_x0                     :8 ,	// 7:0
	reg_fd_gain_x1                     :8 ,	// 15:8
	reg_fd_gain_y0                     :8 ,	// 23:16
	reg_fd_gain_y1                     :8 ;	// 31:24
}PE_M17C0_SR_SHP_MNR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009350L shp_win2_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en                 :1 ,	// 0:0
	reg_win_dp_win1_en                 :1 ,	// 1:1
	reg_win_dp_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside             :1 ,	// 6:6
	reg_win_dp_win_en                  :1 ,	// 7:7
	reg_win_dp_bdr_alpha               :5 ,	// 12:8
	reg_win_dp_bdr_wid                 :2 ,	// 14:13
	reg_win_dp_bdr_en                  :1 ,	// 15:15
	reg_win_dp_cr5                     :5 ,	// 20:16
	reg_win_dp_cb5                     :5 ,	// 25:21
	reg_win_dp_yy6                     :6 ;	// 31:26
}PE_M17C0_SR_SHP_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009354L shp_win2_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009358L shp_win2_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900935cL shp_win2_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009360L shp_win2_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90093a0L shp_win3_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win0_en                 :1 ,	// 0:0
	reg_win_dj_win1_en                 :1 ,	// 1:1
	reg_win_dj_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_win_outside             :1 ,	// 6:6
	reg_win_dj_win_en                  :1 ,	// 7:7
	reg_win_dj_bdr_alpha               :5 ,	// 12:8
	reg_win_dj_bdr_wid                 :2 ,	// 14:13
	reg_win_dj_bdr_en                  :1 ,	// 15:15
	reg_win_dj_cr5                     :5 ,	// 20:16
	reg_win_dj_cb5                     :5 ,	// 25:21
	reg_win_dj_yy6                     :6 ;	// 31:26
}PE_M17C0_SR_SHP_WIN3_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90093a4L shp_win3_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN3_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90093a8L shp_win3_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN3_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90093acL shp_win3_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN3_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90093b0L shp_win3_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_M17C0_SR_SHP_WIN3_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90093f0L shp_debug_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_enable_debug_mode     :1 ,	// 0:0
	reg_dbg_disp_status_enable         :1 ,	// 1:1
	reg_dbg_disp_debug_mode            :1 ,	// 2:2
	reg_dbg_disp_show_dce_blur         :1 ,	// 3:3
	reserved01                         :5 ,	// reserved
	reg_dbg_disp_show_sqm2             :1 ,	// 9:9
	reg_dbg_disp_sqm2_debug_image      :4 ,	// 13:10
	reserved02                         :1 ,	// reserved
	reg_dbg_disp_show_bbd              :2 ,	// 16:15
	reg_dbg_disp_bbd_line_width        :3 ,	// 19:17
	reg_dbg_disp_show_apl              :1 ;	// 20:20
}PE_M17C0_SR_SHP_DEBUG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90093f4L shp_debug_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_yc_debug_en           :1 ,	// 0:0
	reg_dbg_disp_force_yy_enable       :1 ,	// 1:1
	reg_dbg_disp_force_cb_enable       :1 ,	// 2:2
	reg_dbg_disp_force_cr_enable       :1 ,	// 3:3
	reg_dbg_disp_yc_debug_mode_sel     :3 ;	// 6:4
}PE_M17C0_SR_SHP_DEBUG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90093f8L shp_debug_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_force_yy              :10,	// 9:0
	reg_dbg_disp_force_cb              :10,	// 19:10
	reg_dbg_disp_force_cr              :10;	// 29:20
}PE_M17C0_SR_SHP_DEBUG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009600L shp_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_vcnt                       :12,	// 11:0
	reg_mon_va_pe1_in                  :1 ,	// 12:12
	reg_mon_va_pe1_out                 :1 ,	// 13:13
	reserved01                         :2 ,	// reserved
	reg_mon_vcnt2                      :12;	// 27:16
}PE_M17C0_SR_SHP_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009604L shp_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_M17C0_SR_SHP_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009608L shp_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_M17C0_SR_SHP_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900960cL shp_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_vert_cnt               :12;	// 11:0
}PE_M17C0_SR_SHP_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009610L shp_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_M17C0_SR_SHP_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009614L shp_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_M17C0_SR_SHP_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009618L shp_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900961cL shp_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc90096a0L shp_coring_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_CORING_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90096a4L shp_coring_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_CORING_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90096a8L shp_coring_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_CORING_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc90096acL shp_coring_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_CORING_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc90096e0L shp_sqm_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_sqm_blur_pixel             :10,	// 9:0
	reg_mon_sqm_sharp_pixel            :10,	// 19:10
	reg_mon_sqm_output                 :10,	// 29:20
	reg_mon_sqm_pc_detect              :1 ;	// 30:30
}PE_M17C0_SR_SHP_SQM_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90096f0L shp_bbd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_bbd_x0                     :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_bbd_y0                     :12;	// 27:16
}PE_M17C0_SR_SHP_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90096f4L shp_bbd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_bbd_x1                     :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_bbd_y1                     :12;	// 27:16
}PE_M17C0_SR_SHP_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90097e0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cvd_pattern_detect                 :1 ,	//reserved
	color_bar                          :1 ,	//reserved
	vfy_glb_en                         :1 ;	//VFILTER_CTRL_01, reg_glb_vflt_en
}PE_M17C0_SR_SHP_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90097e4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90097e8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90097ecL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SR_SHP_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc900a000L sr_psc_y_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :31,	// reserved
	reg_sampling_mode_m1               :1 ,	// 31:31
	reg_th                             :4 ,	// 9:6
	reg_bilinear_on_m1                 :1 ,	// 5:5
	reg_adaptive_on_m1                 :1 ,	// 4:4
	reg_vsc_mode_m1                    :1 ,	// 3:3
	reserved02                         :6 , // reserved
	blending_range                     :2 ;	// 11:10
}PE_M17C0_SR_PSC_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a008L sr_psc_y_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_vosize_m1                      :12;	// 27:16
}PE_M17C0_SR_PSC_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a018L sr_psc_y_insize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_visize_m1                      :12;	// 27:16
}PE_M17C0_SR_PSC_Y_INSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a020L sr_psc_y_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_m1                 :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_phase_off_h_m1                 :9 ;	// 24:16
}PE_M17C0_SR_PSC_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900a024L sr_psc_y_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_m1               :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_numerator_h_m1                 :13;	// 28:16
}PE_M17C0_SR_PSC_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc900a028L sr_psc_y_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_m1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_numerator_v_m1                 :12;	// 27:16
}PE_M17C0_SR_PSC_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900a02cL sr_psc_y_min_max_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_min_max_on_l_h                 :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_min_max_th_l_h                 :9 ,	// 12:4
	reg_adaptive_mode_h                :1 ,	// 13
	reserved02                         :2 ,	// reserved
	reg_min_max_on_l_v                 :1 ,	// 16
	reserved03                         :3 ,	// reserved
	reg_min_max_th_l_v                 :9 ,	// 28:20
	reg_adaptive_mode_v                :1 ,	// 29
	reserved04                         :1 , // reserved
	reg_v_min_max_extend               :1 ;	// 31
}PE_M17C0_SR_PSC_Y_MIN_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a044L sr_psc_y_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v1                          :1 ,	// 0:0
	rnw_v1                             :1 ,	// 1:1
	addr_v1                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a048L sr_psc_y_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a04cL sr_psc_y_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a050L sr_psc_y_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a054L sr_psc_y_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a058L sr_psc_y_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a05cL sr_psc_y_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_v1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_v1                 :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a060L sr_psc_y_v2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v2                          :1 ,	// 0:0
	rnw_v2                             :1 ,	// 1:1
	addr_v2                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_Y_V2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a064L sr_psc_y_v2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a068L sr_psc_y_v2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a06cL sr_psc_y_v2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a070L sr_psc_y_v2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a074L sr_psc_y_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h1                          :1 ,	// 0:0
	rnw_h1                             :1 ,	// 1:1
	addr_h1                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a078L sr_psc_y_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a07cL sr_psc_y_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a080L sr_psc_y_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a084L sr_psc_y_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a088L sr_psc_y_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a08cL sr_psc_y_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_h1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_h1                 :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a090L sr_psc_y_h2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h2                          :1 ,	// 0:0
	rnw_h2                             :1 ,	// 1:1
	addr_h2                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_Y_H2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a094L sr_psc_y_h2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a098L sr_psc_y_h2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a09cL sr_psc_y_h2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a0a0L sr_psc_y_h2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h2                  :12;	// 27:16
}PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA3_T;


/*-----------------------------------------------------------------------------
                             0xc900a100L sr_psc_c_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :3 ,	// reserved
	reg_vsc_mode_g0                    :2 ,	// 4:3
	reg_bilinear_on_g0                 :1 ,	// 5:5
	reg_mode_32p_g0                    :1 ,	// 6:6
	reserved02                         :7 ,	// reserved
	reg_min_max_on_g0                  :1 ,	// 14:14
	reg_min_max_th_g0                  :10,	// 24:15
	reg_v_reverse_g0                   :1 ,	// 25:25
	reserved03                         :1 ,	// reserved
	reg_min_max_on_h_g0                :1 ,	// 27:27
	reg_v_cti_en_g0                    :1 ,	// 28:28
	reg_v_cti_ratio_g0                 :2 ,	// 30:29
	reg_sampling_mode_g0               :1 ;	// 31:31
}PE_M17C0_SR_PSC_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a108L sr_psc_c_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_vosize_m1                      :12;	// 27:16
}PE_M17C0_SR_PSC_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a118L sr_psc_c_insize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_visize_m1                      :12;	// 27:16
}PE_M17C0_SR_PSC_C_INSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a120L sr_psc_c_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_m1                 :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_phase_off_h_m1                 :9 ;	// 24:16
}PE_M17C0_SR_PSC_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900a124L sr_psc_c_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_m1               :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_numerator_h_m1                 :13;	// 28:16
}PE_M17C0_SR_PSC_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc900a128L sr_psc_c_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_m1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_numerator_v_m1                 :12;	// 27:16
}PE_M17C0_SR_PSC_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900a144L sr_psc_c_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v1                          :1 ,	// 0:0
	rnw_v1                             :1 ,	// 1:1
	addr_v1                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a148L sr_psc_c_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a14cL sr_psc_c_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a150L sr_psc_c_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a154L sr_psc_c_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a158L sr_psc_c_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_v1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a15cL sr_psc_c_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_v1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_v1                 :12;	// 27:16
}PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a174L sr_psc_c_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h1                          :1 ,	// 0:0
	rnw_h1                             :1 ,	// 1:1
	addr_h1                            :8 ;	// 9:2
}PE_M17C0_SR_PSC_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a178L sr_psc_c_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a17cL sr_psc_c_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a180L sr_psc_c_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a184L sr_psc_c_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a188L sr_psc_c_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_h1                  :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a18cL sr_psc_c_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_h1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_h1                 :12;	// 27:16
}PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA5_T;

typedef struct
{ 
	PE_M17C0_SR_SHP_CTRL_00_T                            shp_ctrl_00;	//0x0000
	PE_M17C0_SR_SHP_CTRL_01_T                            shp_ctrl_01;	//0x0004
	PE_M17C0_SR_SHP_CTRL_02_T                            shp_ctrl_02;	//0x0008
	UINT32                                            reserved3[41];	//0xc-0xac
	PE_M17C0_SR_SHP_DERH_CTRL_00_T                       shp_derh_ctrl_00;	//0x00B0
	PE_M17C0_SR_SHP_DERH_CTRL_01_T                       shp_derh_ctrl_01;	//0x00B4
	PE_M17C0_SR_SHP_DERH_CTRL_02_T                       shp_derh_ctrl_02;	//0x00B8
	PE_M17C0_SR_SHP_DERH_CTRL_03_T                       shp_derh_ctrl_03;	//0x00BC
	PE_M17C0_SR_SHP_DERH_CTRL_04_T                       shp_derh_ctrl_04;	//0x00C0
	PE_M17C0_SR_SHP_DERH_CTRL_05_T                       shp_derh_ctrl_05;	//0x00C4
	PE_M17C0_SR_SHP_DERH_CTRL_06_T                       shp_derh_ctrl_06;	//0x00C8
	PE_M17C0_SR_SHP_DERH_CTRL_07_T                       shp_derh_ctrl_07;	//0x00CC
	PE_M17C0_SR_SHP_DERH_CTRL_08_T                       shp_derh_ctrl_08;	//0x00D0
	PE_M17C0_SR_SHP_DERH_CTRL_09_T                       shp_derh_ctrl_09;	//0x00D4
	PE_M17C0_SR_SHP_DERH_CTRL_0A_T                       shp_derh_ctrl_0a;	//0x00D8
	PE_M17C0_SR_SHP_DERH_CTRL_0B_T                       shp_derh_ctrl_0b;	//0x00DC
	PE_M17C0_SR_SHP_DERH_CTRL_0C_T                       shp_derh_ctrl_0c;	//0x00E0
	UINT32                                            reserved16[3];	//0xe4-0xec
	PE_M17C0_SR_SHP_DERV_CTRL_0_T                        shp_derv_ctrl_0;	//0x00F0
	PE_M17C0_SR_SHP_DERV_CTRL_1_T                        shp_derv_ctrl_1;	//0x00F4
	PE_M17C0_SR_SHP_DERV_CTRL_2_T                        shp_derv_ctrl_2;	//0x00F8
	PE_M17C0_SR_SHP_DERV_CTRL_3_T                        shp_derv_ctrl_3;	//0x00FC
	UINT32                                            reserved20[4];	//0x100-0x10c
	PE_M17C0_SR_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0x0110
	PE_M17C0_SR_SHP_DP_CTRL_01_T                         shp_dp_ctrl_01;	//0x0114
	PE_M17C0_SR_SHP_DP_CTRL_02_T                         shp_dp_ctrl_02;	//0x0118
	PE_M17C0_SR_SHP_DP_CTRL_03_T                         shp_dp_ctrl_03;	//0x011C
	PE_M17C0_SR_SHP_DP_CTRL_04_T                         shp_dp_ctrl_04;	//0x0120
	PE_M17C0_SR_SHP_DP_CTRL_05_T                         shp_dp_ctrl_05;	//0x0124
	PE_M17C0_SR_SHP_DP_CTRL_06_T                         shp_dp_ctrl_06;	//0x0128
	PE_M17C0_SR_SHP_DP_CTRL_07_T                         shp_dp_ctrl_07;	//0x012C
	PE_M17C0_SR_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0x0130
	PE_M17C0_SR_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0x0134
	PE_M17C0_SR_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0x0138
	PE_M17C0_SR_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0x013C
	PE_M17C0_SR_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0x0140
	PE_M17C0_SR_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0x0144
	PE_M17C0_SR_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0x0148
	PE_M17C0_SR_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0x014C
	PE_M17C0_SR_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0x0150
	PE_M17C0_SR_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0x0154
	PE_M17C0_SR_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0x0158
	PE_M17C0_SR_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0x015C
	PE_M17C0_SR_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0x0160
	UINT32                                            reserved41[3];	//0x164-0x16c
	PE_M17C0_SR_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0x0170
	PE_M17C0_SR_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0x0174
	PE_M17C0_SR_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0x0178
	PE_M17C0_SR_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0x017C
	PE_M17C0_SR_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0x0180
	PE_M17C0_SR_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0x0184
	PE_M17C0_SR_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0x0188
	PE_M17C0_SR_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0x018C
	PE_M17C0_SR_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0x0190
	PE_M17C0_SR_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0x0194
	PE_M17C0_SR_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0x0198
	PE_M17C0_SR_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0x019C
	PE_M17C0_SR_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0x01A0
	UINT32                                            reserved54[3];	//0x1a4-0x1ac
	PE_M17C0_SR_SHP_CORING_CTRL_00_T                     shp_coring_ctrl_00;	//0x01B0
	PE_M17C0_SR_SHP_CORING_CTRL_01_T                     shp_coring_ctrl_01;	//0x01B4
	PE_M17C0_SR_SHP_CORING_CTRL_02_T                     shp_coring_ctrl_02;	//0x01B8
	PE_M17C0_SR_SHP_CORING_CTRL_03_T                     shp_coring_ctrl_03;	//0x01BC
	PE_M17C0_SR_SHP_CORING_CTRL_04_T                     shp_coring_ctrl_04;	//0x01C0
	PE_M17C0_SR_SHP_CORING_CTRL_05_T                     shp_coring_ctrl_05;	//0x01C4
	PE_M17C0_SR_SHP_CORING_CTRL_06_T                     shp_coring_ctrl_06;	//0x01C8
	PE_M17C0_SR_SHP_CORING_CTRL_07_T                     shp_coring_ctrl_07;	//0x01CC
	PE_M17C0_SR_SHP_CORING_CTRL_08_T                     shp_coring_ctrl_08;	//0x01D0
	PE_M17C0_SR_SHP_CORING_CTRL_09_T                     shp_coring_ctrl_09;	//0x01D4
	UINT32                                            reserved64[10];	//0x1d8-0x1fc
	PE_M17C0_SR_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0x0200
	PE_M17C0_SR_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0x0204
	PE_M17C0_SR_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0x0208
	PE_M17C0_SR_SHP_STI_CTRL_01_T                        shp_sti_ctrl_01;	//0x020C
	UINT32                                            reserved68[4];	//0x210-0x21c
	PE_M17C0_SR_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0x0220
	PE_M17C0_SR_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0x0224
	PE_M17C0_SR_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0x0228
	PE_M17C0_SR_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0x022C
	UINT32                                            reserved72[12];	//0x230-0x25c
	PE_M17C0_SR_SHP_SQM_CTRL_00_T                        shp_sqm_ctrl_00;	//0x0260
	PE_M17C0_SR_SHP_SQM_CTRL_01_T                        shp_sqm_ctrl_01;	//0x0264
	PE_M17C0_SR_SHP_SQM_CTRL_02_T                        shp_sqm_ctrl_02;	//0x0268
	PE_M17C0_SR_SHP_SQM_CTRL_03_T                        shp_sqm_ctrl_03;	//0x026C
	PE_M17C0_SR_SHP_SQM_CTRL_04_T                        shp_sqm_ctrl_04;	//0x0270
	PE_M17C0_SR_SHP_SQM_CTRL_05_T                        shp_sqm_ctrl_05;	//0x0274
	UINT32                                            reserved78;	//0x278
	UINT32                                            reserved00;	//0x027C-0x027C
	PE_M17C0_SR_SHP_BBD_CTRL_00_T                        shp_bbd_ctrl_00;	//0x0280
	PE_M17C0_SR_SHP_BBD_CTRL_01_T                        shp_bbd_ctrl_01;	//0x0284
	PE_M17C0_SR_SHP_BBD_CTRL_02_T                        shp_bbd_ctrl_02;	//0x0288
	UINT32                                            reserved82[5];	//0x28c-0x29c
	PE_M17C0_SR_SHP_TGEN_CTRL_00_T                       shp_tgen_ctrl_00;	//0x02A0
	PE_M17C0_SR_SHP_TGEN_CTRL_01_T                       shp_tgen_ctrl_01;	//0x02A4
	PE_M17C0_SR_SHP_TGEN_CTRL_02_T                       shp_tgen_ctrl_02;	//0x02A8
	PE_M17C0_SR_SHP_TGEN_CTRL_03_T                       shp_tgen_ctrl_03;	//0x02AC
	PE_M17C0_SR_SHP_TGEN_CTRL_04_T                       shp_tgen_ctrl_04;	//0x02B0
	PE_M17C0_SR_SHP_TGEN_CTRL_05_T                       shp_tgen_ctrl_05;	//0x02B4
	PE_M17C0_SR_SHP_TGEN_CTRL_06_T                       shp_tgen_ctrl_06;	//0x02B8
	PE_M17C0_SR_SHP_TGEN_CTRL_07_T                       shp_tgen_ctrl_07;	//0x02BC
	PE_M17C0_SR_SHP_TGEN_CTRL_08_T                       shp_tgen_ctrl_08;	//0x02C0
	PE_M17C0_SR_SHP_TGEN_CTRL_09_T                       shp_tgen_ctrl_09;	//0x02C4
	PE_M17C0_SR_SHP_CONTRAST_CTRL_00_T                   shp_contrast_ctrl_00;	//0x02C8
	PE_M17C0_SR_SHP_CONTRAST_CTRL_01_T                   shp_contrast_ctrl_01;	//0x02CC
	PE_M17C0_SR_SHP_CONTRAST_CTRL_02_T                   shp_contrast_ctrl_02;	//0x02D0
	PE_M17C0_SR_SHP_CONTRAST_CTRL_03_T                   shp_contrast_ctrl_03;	//0x02D4
	PE_M17C0_SR_SHP_CONTRAST_CTRL_04_T                   shp_contrast_ctrl_04;	//0x02D8
	PE_M17C0_SR_SHP_MNR_CTRL_00_T                        shp_mnr_ctrl_00;	//0x02DC
	PE_M17C0_SR_SHP_MNR_CTRL_01_T                        shp_mnr_ctrl_01;	//0x02E0
	PE_M17C0_SR_SHP_MNR_CTRL_02_T                        shp_mnr_ctrl_02;	//0x02E4
	UINT32                                            reserved100[26];	//0x2e8-0x34c
	PE_M17C0_SR_SHP_WIN2_CTRL_00_T                       shp_win2_ctrl_00;	//0x0350
	PE_M17C0_SR_SHP_WIN2_CTRL_01_T                       shp_win2_ctrl_01;	//0x0354
	PE_M17C0_SR_SHP_WIN2_CTRL_02_T                       shp_win2_ctrl_02;	//0x0358
	PE_M17C0_SR_SHP_WIN2_CTRL_03_T                       shp_win2_ctrl_03;	//0x035C
	PE_M17C0_SR_SHP_WIN2_CTRL_04_T                       shp_win2_ctrl_04;	//0x0360
	UINT32                                            reserved105[15];	//0x364-0x39c
	PE_M17C0_SR_SHP_WIN3_CTRL_00_T                       shp_win3_ctrl_00;	//0x03A0
	PE_M17C0_SR_SHP_WIN3_CTRL_01_T                       shp_win3_ctrl_01;	//0x03A4
	PE_M17C0_SR_SHP_WIN3_CTRL_02_T                       shp_win3_ctrl_02;	//0x03A8
	PE_M17C0_SR_SHP_WIN3_CTRL_03_T                       shp_win3_ctrl_03;	//0x03AC
	PE_M17C0_SR_SHP_WIN3_CTRL_04_T                       shp_win3_ctrl_04;	//0x03B0
	UINT32                                            reserved110[15];	//0x3b4-0x3ec
	PE_M17C0_SR_SHP_DEBUG_CTRL_00_T                      shp_debug_ctrl_00;	//0x03F0
	PE_M17C0_SR_SHP_DEBUG_CTRL_01_T                      shp_debug_ctrl_01;	//0x03F4
	PE_M17C0_SR_SHP_DEBUG_CTRL_02_T                      shp_debug_ctrl_02;	//0x03F8
	UINT32                                            reserved113[129];	//0x3fc-0x5fc
	PE_M17C0_SR_SHP_STAT_00_T                            shp_stat_00;	//0x0600
	PE_M17C0_SR_SHP_STAT_01_T                            shp_stat_01;	//0x0604
	PE_M17C0_SR_SHP_STAT_02_T                            shp_stat_02;	//0x0608
	PE_M17C0_SR_SHP_STAT_03_T                            shp_stat_03;	//0x060C
	PE_M17C0_SR_SHP_STAT_04_T                            shp_stat_04;	//0x0610
	PE_M17C0_SR_SHP_STAT_05_T                            shp_stat_05;	//0x0614
	PE_M17C0_SR_SHP_STAT_06_T                            shp_stat_06;	//0x0618
	PE_M17C0_SR_SHP_STAT_07_T                            shp_stat_07;	//0x061C
	UINT32                                            reserved121[32];	//0x620-0x69c
	PE_M17C0_SR_SHP_CORING_STAT_00_T                     shp_coring_stat_00;	//0x06A0
	PE_M17C0_SR_SHP_CORING_STAT_01_T                     shp_coring_stat_01;	//0x06A4
	PE_M17C0_SR_SHP_CORING_STAT_02_T                     shp_coring_stat_02;	//0x06A8
	PE_M17C0_SR_SHP_CORING_STAT_03_T                     shp_coring_stat_03;	//0x06AC
	UINT32                                            reserved125[12];	//0x6b0-0x6dc
	PE_M17C0_SR_SHP_SQM_STAT_00_T                        shp_sqm_stat_00;	//0x06E0
	UINT32                                            reserved126[3];	//0x6e4-0x6ec
	PE_M17C0_SR_SHP_BBD_STAT_00_T                        shp_bbd_stat_00;	//0x06F0
	PE_M17C0_SR_SHP_BBD_STAT_01_T                        shp_bbd_stat_01;	//0x06F4
	UINT32                                            reserved128[58];	//0x6f8-0x7dc
	PE_M17C0_SR_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0x07E0
	PE_M17C0_SR_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0x07E4
	PE_M17C0_SR_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0x07E8
	PE_M17C0_SR_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0x07EC
}PE_SR_SHP_REG_M17C0_T;

typedef struct
{ 
	PE_M17C0_SR_PSC_Y_CTRL_T                          sr_psc_y_ctrl;	//0x0000
	UINT32                                            reserved1;	//0x4
	PE_M17C0_SR_PSC_Y_OUTSIZE_T                       sr_psc_y_outsize;	//0x0008
	UINT32                                            reserved2[3];	//0xc-0x14
	PE_M17C0_SR_PSC_Y_INSIZE_T                        sr_psc_y_insize;	//0x0018
	UINT32                                            reserved3;	//0x1c
	PE_M17C0_SR_PSC_Y_PHASE_OFFSET_T                  sr_psc_y_phase_offset;	//0x0020
	PE_M17C0_SR_PSC_Y_SAMPLING_H_T                    sr_psc_y_sampling_h;	//0x0024
	PE_M17C0_SR_PSC_Y_SAMPLING_V_T                    sr_psc_y_sampling_v;	//0x0028
	PE_M17C0_SR_PSC_Y_MIN_MAX_CTRL_T                  sr_psc_y_min_max_ctrl;	//0x002C
	UINT32                                            reserved7[5];	//0x30-0x40
	PE_M17C0_SR_PSC_Y_V1_FIR_COEF_CTRL_T              sr_psc_y_v1_fir_coef_ctrl;	//0x0044
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA0_T           sr_psc_y_v1_y_fir_coef_data0;	//0x0048
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA1_T           sr_psc_y_v1_y_fir_coef_data1;	//0x004C
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA2_T           sr_psc_y_v1_y_fir_coef_data2;	//0x0050
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA3_T           sr_psc_y_v1_y_fir_coef_data3;	//0x0054
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA4_T           sr_psc_y_v1_y_fir_coef_data4;	//0x0058
	PE_M17C0_SR_PSC_Y_V1_Y_FIR_COEF_DATA5_T           sr_psc_y_v1_y_fir_coef_data5;	//0x005C
	PE_M17C0_SR_PSC_Y_V2_FIR_COEF_CTRL_T              sr_psc_y_v2_fir_coef_ctrl;	//0x0060
	PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA0_T           sr_psc_y_v2_y_fir_coef_data0;	//0x0064
	PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA1_T           sr_psc_y_v2_y_fir_coef_data1;	//0x0068
	PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA2_T           sr_psc_y_v2_y_fir_coef_data2;	//0x006C
	PE_M17C0_SR_PSC_Y_V2_Y_FIR_COEF_DATA3_T           sr_psc_y_v2_y_fir_coef_data3;	//0x0070
	PE_M17C0_SR_PSC_Y_H1_FIR_COEF_CTRL_T              sr_psc_y_h1_fir_coef_ctrl;	//0x0074
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA0_T           sr_psc_y_h1_y_fir_coef_data0;	//0x0078
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA1_T           sr_psc_y_h1_y_fir_coef_data1;	//0x007C
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA2_T           sr_psc_y_h1_y_fir_coef_data2;	//0x0080
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA3_T           sr_psc_y_h1_y_fir_coef_data3;	//0x0084
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA4_T           sr_psc_y_h1_y_fir_coef_data4;	//0x0088
	PE_M17C0_SR_PSC_Y_H1_Y_FIR_COEF_DATA5_T           sr_psc_y_h1_y_fir_coef_data5;	//0x008C
	PE_M17C0_SR_PSC_Y_H2_FIR_COEF_CTRL_T              sr_psc_y_h2_fir_coef_ctrl;	//0x0090
	PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA0_T           sr_psc_y_h2_y_fir_coef_data0;	//0x0094
	PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA1_T           sr_psc_y_h2_y_fir_coef_data1;	//0x0098
	PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA2_T           sr_psc_y_h2_y_fir_coef_data2;	//0x009C
	PE_M17C0_SR_PSC_Y_H2_Y_FIR_COEF_DATA3_T           sr_psc_y_h2_y_fir_coef_data3;	//0x00A0
}PE_SR_PSC_Y_REG_M17C0_T;

typedef struct
{ 
	PE_M17C0_SR_PSC_C_CTRL_T                          sr_psc_c_ctrl;	//0x0000
	UINT32                                            reserved1;	//0x4
	PE_M17C0_SR_PSC_C_OUTSIZE_T                       sr_psc_c_outsize;	//0x0008
	UINT32                                            reserved2[3];	//0xc-0x14
	PE_M17C0_SR_PSC_C_INSIZE_T                        sr_psc_c_insize;	//0x0018
	UINT32                                            reserved3;	//0x1c
	PE_M17C0_SR_PSC_C_PHASE_OFFSET_T                  sr_psc_c_phase_offset;	//0x0020
	PE_M17C0_SR_PSC_C_SAMPLING_H_T                    sr_psc_c_sampling_h;	//0x0024
	PE_M17C0_SR_PSC_C_SAMPLING_V_T                    sr_psc_c_sampling_v;	//0x0028
	UINT32                                            reserved6[6];	//0x2c-0x40
	PE_M17C0_SR_PSC_C_V1_FIR_COEF_CTRL_T              sr_psc_c_v1_fir_coef_ctrl;	//0x0044
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA0_T           sr_psc_c_v1_y_fir_coef_data0;	//0x0048
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA1_T           sr_psc_c_v1_y_fir_coef_data1;	//0x004C
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA2_T           sr_psc_c_v1_y_fir_coef_data2;	//0x0050
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA3_T           sr_psc_c_v1_y_fir_coef_data3;	//0x0054
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA4_T           sr_psc_c_v1_y_fir_coef_data4;	//0x0058
	PE_M17C0_SR_PSC_C_V1_Y_FIR_COEF_DATA5_T           sr_psc_c_v1_y_fir_coef_data5;	//0x005C
	UINT32                                            reserved13[5];	//0x60-0x70
	PE_M17C0_SR_PSC_C_H1_FIR_COEF_CTRL_T              sr_psc_c_h1_fir_coef_ctrl;	//0x0074
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA0_T           sr_psc_c_h1_y_fir_coef_data0;	//0x0078
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA1_T           sr_psc_c_h1_y_fir_coef_data1;	//0x007C
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA2_T           sr_psc_c_h1_y_fir_coef_data2;	//0x0080
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA3_T           sr_psc_c_h1_y_fir_coef_data3;	//0x0084
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA4_T           sr_psc_c_h1_y_fir_coef_data4;	//0x0088
	PE_M17C0_SR_PSC_C_H1_Y_FIR_COEF_DATA5_T           sr_psc_c_h1_y_fir_coef_data5;	//0x008C
}PE_SR_PSC_C_REG_M17C0_T;
#endif
