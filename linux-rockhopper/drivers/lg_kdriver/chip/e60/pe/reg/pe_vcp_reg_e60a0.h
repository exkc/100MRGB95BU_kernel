#ifndef _PE_VCP_REG_E60A0_H_
#define _PE_VCP_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC902A400 RW
	UINT32 mask_pic_init_y_mux_u0_cdc       :1;	//0 //
	UINT32 mask_pic_init_c_mux_u0_cdc       :1;	//1 //
	UINT32 mask_pic_init_y_mux_u1_cdc       :1;	//2 //
	UINT32 mask_pic_init_c_mux_u1_cdc       :1;	//3 //
	UINT32 resvd0                           :4;
	UINT32 mask_pic_init_y_mux_m_wcp        :1;	//8 //
	UINT32 mask_pic_init_c_mux_m_wcp        :1;	//9 //
	UINT32 reserved0                        :2;	//10 //
	UINT32 mask_pic_init_y_mux_ms_wcp       :1;	//12 //
	UINT32 mask_pic_init_c_mux_ms_wcp       :1;	//13 //
	UINT32 resvd1                           :2;
	UINT32 mask_pic_start_y_mux_u0_cdc      :1;	//16 //
	UINT32 mask_pic_start_c_mux_u0_cdc      :1;	//17 //
	UINT32 mask_pic_start_y_mux_u1_cdc      :1;	//18 //
	UINT32 mask_pic_start_c_mux_u1_cdc      :1;	//19 //
	UINT32 resvd2                           :4;
	UINT32 mask_pic_start_y_mux_m_wcp       :1;	//24 //
	UINT32 mask_pic_start_c_mux_m_wcp       :1;	//25 //
	UINT32 reserved1                        :2;	//26 //
	UINT32 resvd3                           :4;
	};
}PE_E60_VCP_DISP_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A404 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_DISP_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A408 RW
	UINT32 set_inverse_3d_lr                :1;	//0 //
	UINT32 vcp_u1_disp_clk_cg               :1;	//1 //VCP U1 Disp Clock Gating ON	0 := Off	1 := On
	UINT32 resvd0                           :2;
	UINT32 wcp_m_mix_enable                 :2;	//5:4	//for debugging	"00" := main default.	"01" = PIP/R2 full video
	UINT32 cg_disable                       :1;	//6 //0 : Clock gating, 1 : disable CG
	UINT32 resvd1                           :1;
	UINT32 en_bypass_sync_my                :1;	//8 //
	UINT32 en_bypass_sync_mc                :1;	//9 //
	UINT32 en_bypass_sync_sy                :1;	//10 //
	UINT32 en_bypass_sync_sc                :1;	//11 //
	UINT32 resvd2                           :20;
	};
}PE_E60_VCP_DISP_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A40C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_DISP_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A410 RW
	UINT32 u0_cdc_y_sync_sel                :2;	//1:0	//"00" := main display sync	"01" = sub display sync
	UINT32 u0_cdc_c_sync_sel                :2;	//3:2	//"00" := main display sync	"01" = sub display sync
	UINT32 u1_cdc_y_sync_sel                :2;	//5:4	//"00" := main display sync	"01" = sub display sync
	UINT32 u1_cdc_c_sync_sel                :2;	//7:6	//"00" := main display sync	"01" = sub display sync
	UINT32 resvd0                           :8;
	UINT32 mon_u0_cdc_y_pi_ps_pos_sel       :2;	//17:16	//"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync	"11" = enable monitor for SR sync
	UINT32 mon_u0_cdc_c_pi_ps_pos_sel       :2;	//19:18	//"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 mon_u1_cdc_y_pi_ps_pos_sel       :2;	//21:20	//"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 mon_u1_cdc_c_pi_ps_pos_sel       :2;	//23:22	//"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 resvd1                           :8;
	};
}PE_E60_VCP_CDC_MV_SYNC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A414 RW
	UINT32 u0_cdc_y_disp_sreset             :1;	//0 //CDC_DISP sreset
	UINT32 u0_cdc_c_disp_sreset             :1;	//1 //CDC_DISP sreset
	UINT32 u1_cdc_y_disp_sreset             :1;	//2 //CDC_DISP sreset
	UINT32 u1_cdc_c_disp_sreset             :1;	//3 //CDC_DISP sreset
	UINT32 resvd                            :28;
	};
}PE_E60_VCP_CDC_MV_RST_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A418 RO
	UINT32 reg_420_en                       :1;	//0 //0 : bypass	1 : enable
	UINT32 reg_yy_in_sel                    :1;	//1 //0 : Y0(Cb), Y1(Cr)	1 : Y0(Cr), Y1(Cb)
	UINT32 reg_yy_out_sel                   :2;	//3:2	//0 : YY, 1 : Cb, 2 : Cr
	UINT32 reg_cb_out_sel                   :2;	//5:4	//0 : Cb, 1 : Cr, 2 : YY
	UINT32 reg_cr_out_sel                   :2;	//7:6	//0 : Cr, 1 : YY, 2: Cb
	UINT32 reg_va_srt_num                   :8;	//15:8	//hsync cont 8
	UINT32 reg_last_line                    :14;	//29:16	//last line 4320
	UINT32 resvd                            :2;
	};
}PE_E60_VCP_420_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A41C RO
	UINT32 tdata0                           :32;
	};
}REG_VCP_DISP__T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A420 RW
	UINT32 cdc_win_o_pos_y                  :14;	//13:0	//min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//28:16	//min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U0_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A424 RW
	UINT32 cdc_win_o_size_y                 :14;	//13:0	//min:0, max:4320
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//28:16	//min:0, max:7680
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U0_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A428 RW
	UINT32 resvd0                           :4;
	UINT32 ramp_pat_en                      :2;	//5:4	//"00" := bypass	"01" = diagonal
	UINT32 mpg_o_color_sel                  :2;	//7:6	//"00" := YC	"01" = Y ONLY	"10" = C ONLY	"11" = peaking
	UINT32 resvd1                           :8;
	UINT32 peaking_en                       :1;	//16 //peaking control enable
	UINT32 peak_min_max_clip                :1;	//17 //min max clipping
	UINT32 resvd2                           :2;
	UINT32 peak_even_odd_sel                :1;	//20 //even odd sel
	UINT32 reg_odd_size_dbg                 :1;	//21 //boundary process of odd size
	UINT32 resvd3                           :2;
	UINT32 peak_gain                        :8;	//31:24	//0x00~0xFF (0 is bypass)
	};
}PE_E60_VCP_U0_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A42C RW
	UINT32 peak_hsize                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_VCP_U0_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A430 RW
	UINT32 cdc_voffset                      :5;	//4:0	//CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//5 //
	UINT32 cdc_auto_v_half                  :1;	//6 //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//7 //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//10:8	//"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//11 //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//14:12	//"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//18:16	//"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//19 //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//21:20	//"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//22 //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//27:24	//"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//31:28	//"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_E60_VCP_U0_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A434 RW
	UINT32 nactive_color_cr                 :8;	//7:0	//
	UINT32 nactive_color_cb                 :8;	//15:8	//
	UINT32 nactive_color_y                  :8;	//23:16	//
	UINT32 nactive_window_end_ctrl          :3;	//26:24	//"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//30:28	//"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//31 //
	};
}PE_E60_VCP_U0_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A438 RW
	UINT32 set_pic_init_y_mux_u0_cdc        :4;	//3:0	//"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u0_cdc       :4;	//7:4	//"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//9:8	//when sel_de_type_manual = 01	inc_cdc_dei delay or (0~3)
	UINT32 sel_de_type_manual               :2;	//11:10	//00 : AUTO_DE_TYPE_NEW	01 :  Manual mode	10 : AUTO_DE_TYPE_OLD
	UINT32 cdc_debug                        :1;	//12 //for debug
	UINT32 flush_end                        :1;	//13 //X left shift mode (
	UINT32 resvd0                           :2;
	UINT32 cdc_xpos_end                     :14;	//29:16	//for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//31 //for debug
	};
}PE_E60_VCP_U0_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A43C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_U0_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A440 RW
	UINT32 cdc_voffset                      :5;	//4:0	//CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//5 //
	UINT32 cdc_auto_v_half                  :1;	//6 //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//7 //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//10:8	//"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//11 //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//14:12	//"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//18:16	//"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//19 //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//21:20	//"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//22 //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//27:24	//"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//31:28	//"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_E60_VCP_U0_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A444 RW
	UINT32 nactive_color_cr                 :8;	//7:0	//
	UINT32 nactive_color_cb                 :8;	//15:8	//
	UINT32 nactive_color_y                  :8;	//23:16	//
	UINT32 nactive_window_end_ctrl          :3;	//26:24	//"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//30:28	//"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//31 //
	};
}PE_E60_VCP_U0_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A448 RW
	UINT32 set_pic_init_c_mux_u0_cdc        :4;	//3:0	//"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u0_cdc       :4;	//7:4	//"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//9:8	//for dubug
	UINT32 sel_de_type_manual               :2;	//11:10	//for debug
	UINT32 cdc_debug                        :1;	//12 //for debug
	UINT32 resvd0                           :3;
	UINT32 cdc_xpos_end                     :14;	//29:16	//for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//31 //for debug
	};
}PE_E60_VCP_U0_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A44C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_U0_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A450 RW
	UINT32 cdc_win_o_pos_y                  :14;	//13:0	//min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//28:16	//min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U1_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A454 RW
	UINT32 cdc_win_o_size_y                 :14;	//13:0	//min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//28:16	//min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U1_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A458 RW
	UINT32 resvd0                           :4;
	UINT32 ramp_pat_en                      :2;	//5:4	//"00" := bypass	"01" = diagonal
	UINT32 mpg_o_color_sel                  :2;	//7:6	//"00" := YC	"01" = Y ONLY	"10" = C ONLY	"11" = peaking
	UINT32 resvd1                           :8;
	UINT32 peaking_en                       :1;	//16 //peaking control enable
	UINT32 peak_min_max_clip                :1;	//17 //min max clipping
	UINT32 resvd2                           :2;
	UINT32 peak_even_odd_sel                :1;	//20 //even odd sel
	UINT32 reg_odd_size_dbg                 :1;	//21 //boundary process of odd size
	UINT32 resvd3                           :2;
	UINT32 peak_gain                        :8;	//31:24	//0x00~0xFF (0 is bypass)
	};
}PE_E60_VCP_U1_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A45C RW
	UINT32 peak_hsize                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_VCP_U1_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A460 RW
	UINT32 cdc_voffset                      :5;	//4:0	//CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//5 //
	UINT32 cdc_auto_v_half                  :1;	//6 //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//7 //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//10:8	//"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//11 //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//14:12	//"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//18:16	//"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//19 //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//21:20	//"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//22 //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//27:24	//"0000" := video full.	"0001" = video window.	"0010" = video R2(T3C).	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//31:28	//"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_E60_VCP_U1_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A464 RW
	UINT32 nactive_color_cr                 :8;	//7:0	//
	UINT32 nactive_color_cb                 :8;	//15:8	//
	UINT32 nactive_color_y                  :8;	//23:16	//
	UINT32 nactive_window_end_ctrl          :3;	//26:24	//"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//30:28	//"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//31 //
	};
}PE_E60_VCP_U1_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A468 RW
	UINT32 set_pic_init_y_mux_u1_cdc        :4;	//3:0	//"0000" := none	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u1_cdc       :4;	//7:4	//"0000" := none	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//9:8	//for dubug
	UINT32 sel_de_type_manual               :2;	//11:10	//for debug
	UINT32 cdc_debug                        :1;	//12 //for debug
	UINT32 resvd0                           :3;
	UINT32 cdc_xpos_end                     :14;	//29:16	//for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//31 //for debug
	};
}PE_E60_VCP_U1_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A46C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_U1_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A470 RW
	UINT32 cdc_voffset                      :5;	//4:0	//CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//5 //
	UINT32 cdc_auto_v_half                  :1;	//6 //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//7 //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//10:8	//"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//11 //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//14:12	//"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//18:16	//"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//19 //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//21:20	//"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//22 //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//27:24	//"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//31:28	//"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_E60_VCP_U1_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A474 RW
	UINT32 nactive_color_cr                 :8;	//7:0	//
	UINT32 nactive_color_cb                 :8;	//15:8	//
	UINT32 nactive_color_y                  :8;	//23:16	//
	UINT32 nactive_window_end_ctrl          :3;	//26:24	//"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//30:28	//"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//31 //
	};
}PE_E60_VCP_U1_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A478 RW
	UINT32 set_pic_init_c_mux_u1_cdc        :4;	//3:0	//"0000" := none	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u1_cdc       :4;	//7:4	//"0000" := none	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//9:8	//for dubug
	UINT32 sel_de_type_manual               :2;	//11:10	//for debug
	UINT32 cdc_debug                        :1;	//12 //for debug
	UINT32 resvd0                           :3;
	UINT32 cdc_xpos_end                     :14;	//29:16	//for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//31 //for debug
	};
}PE_E60_VCP_U1_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A47C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_U1_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A480 RW
	UINT32 cdc_win_o_pos_y_aux              :14;	//13:0	//min:0, max:4320
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//28:16	//min:0, max:7680
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U0_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A484 RW
	UINT32 cdc_win_o_size_y_aux             :14;	//13:0	//min:0, max:4320
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//28:16	//min:0, max:7680
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//31 //
	};
}PE_E60_VCP_U0_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A488 RW
	UINT32 cdc_win_o_pos_y_aux              :14;	//13:0	//min:0, max:4320
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//28:16	//min:0, max:7680
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_U1_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A48C RW
	UINT32 cdc_win_o_size_y_aux             :14;	//13:0	//min:0, max:4320
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//28:16	//min:0, max:7680
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//31 //
	};
}PE_E60_VCP_U1_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4E0 RW
	UINT32 vsync                            :16;	//15:0	//10
	UINT32 vfp                              :16;	//31:16	//8
	};
}PE_E60_VCP_SG_MVY_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4E4 RW
	UINT32 va                               :16;	//15:0	//2160
	UINT32 vbp                              :16;	//31:16	//72
	};
}PE_E60_VCP_SG_MVY_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4E8 RW
	UINT32 hsync                            :16;	//15:0	//88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//31:16	//176/2=88 for dual channel(E,O)
	};
}PE_E60_VCP_SG_MVY_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4EC RW
	UINT32 ha                               :16;	//15:0	//3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//31:16	//296/2=148 for dual channel(E,O)
	};
}PE_E60_VCP_SG_MVY_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4F0 RW
	UINT32 line_start_pos                   :16;	//15:0	//should be set to (HFP value+8)
	UINT32 sync_i_h_sel                     :1;	//16 //
	UINT32 sync_i_v_sel                     :1;	//17 //
	UINT32 sync_i_inv_ha                    :1;	//18 //
	UINT32 sync_i_inv_va                    :1;	//19 //
	UINT32 sync_o_sel_ha                    :1;	//20 //
	UINT32 sync_o_sel_va                    :1;	//21 //
	UINT32 sync_o_sel_hs                    :1;	//22 //
	UINT32 sync_o_sel_vs                    :1;	//23 //
	UINT32 tp_update_hv_zero                :1;	//24 //
	UINT32 resvd0                           :3;
	UINT32 manual_cnt_h_value_en            :1;	//28 //
	UINT32 manual_cnt_v_value_en            :1;	//29 //
	UINT32 resvd1                           :1;
	UINT32 update_force                     :1;	//31 //
	};
}PE_E60_VCP_SG_MVY_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4F4 RW
	UINT32 sync_h_dly                       :16;	//15:0	//
	UINT32 sync_v_dly                       :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVY_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4F8 RW
	UINT32 manual_cnt_h_value               :16;	//15:0	//
	UINT32 manual_cnt_v_value               :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVY_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A4FC RW
	UINT32 auto_ha_delay                    :15;	//14:0	//
	UINT32 auto_general_en                  :1;	//15 //general delay block enable
	UINT32 auto_va_delay                    :15;	//30:16	//
	UINT32 auto_seamless                    :1;	//31 //
	};
}PE_E60_VCP_SG_MVY_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A500 RW
	UINT32 auto_hs_delay                    :15;	//14:0	//
	UINT32 auto_general_en                  :1;	//15 //general delay block enable
	UINT32 auto_vs_delay                    :15;	//30:16	//
	UINT32 auto_seamless                    :1;	//31 //
	};
}PE_E60_VCP_SG_MVY_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A504 RW
	UINT32 resvd                            :31;
	UINT32 sync_out_disable                 :1;	//31 //
	};
}PE_E60_VCP_SG_MVY_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A510 RW
	UINT32 vsync                            :16;	//15:0	//10
	UINT32 vfp                              :16;	//31:16	//8
	};
}PE_E60_VCP_SG_MVC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A514 RW
	UINT32 va                               :16;	//15:0	//2160
	UINT32 vbp                              :16;	//31:16	//72
	};
}PE_E60_VCP_SG_MVC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A518 RW
	UINT32 hsync                            :16;	//15:0	//88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//31:16	//176/2=88 for dual channel(E,O)
	};
}PE_E60_VCP_SG_MVC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A51C RW
	UINT32 ha                               :16;	//15:0	//3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//31:16	//296/2=148 for dual channel(E,O)
	};
}PE_E60_VCP_SG_MVC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A520 RW
	UINT32 line_start_pos                   :16;	//15:0	//should be set to (HFP value+8)
	UINT32 sync_i_h_sel                     :1;	//16 //
	UINT32 sync_i_v_sel                     :1;	//17 //
	UINT32 sync_i_inv_ha                    :1;	//18 //
	UINT32 sync_i_inv_va                    :1;	//19 //
	UINT32 sync_o_sel_ha                    :1;	//20 //
	UINT32 sync_o_sel_va                    :1;	//21 //
	UINT32 sync_o_sel_hs                    :1;	//22 //
	UINT32 sync_o_sel_vs                    :1;	//23 //
	UINT32 tp_update_hv_zero                :1;	//24 //
	UINT32 resvd0                           :3;
	UINT32 manual_cnt_h_value_en            :1;	//28 //
	UINT32 manual_cnt_v_value_en            :1;	//29 //
	UINT32 resvd1                           :1;
	UINT32 update_force                     :1;	//31 //
	};
}PE_E60_VCP_SG_MVC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A524 RW
	UINT32 sync_h_dly                       :16;	//15:0	//
	UINT32 sync_v_dly                       :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A528 RW
	UINT32 manual_cnt_h_value               :16;	//15:0	//
	UINT32 manual_cnt_v_value               :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVC_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A52C RW
	UINT32 auto_ha_delay                    :15;	//14:0	//
	UINT32 auto_general_en                  :1;	//15 //general delay block enable
	UINT32 auto_va_delay                    :15;	//30:16	//
	UINT32 auto_seamless                    :1;	//31 //
	};
}PE_E60_VCP_SG_MVC_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A530 RW
	UINT32 auto_hs_delay                    :15;	//14:0	//
	UINT32 auto_general_en                  :1;	//15 //general delay block enable
	UINT32 auto_vs_delay                    :15;	//30:16	//
	UINT32 auto_seamless                    :1;	//31 //
	};
}PE_E60_VCP_SG_MVC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A534 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_VCP_SG_MVC_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A538 RO
	UINT32 vcp_u0y_pic_init_hpos            :16;	//15:0	//
	UINT32 vcp_u0y_pic_init_vpos            :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U0Y_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A53C RO
	UINT32 vcp_u0y_pic_start_hpos           :16;	//15:0	//
	UINT32 vcp_u0y_pic_start_vpos           :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U0Y_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A540 RO
	UINT32 vcp_u0c_pic_init_hpos            :16;	//15:0	//
	UINT32 vcp_u0c_pic_init_vpos            :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U0C_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A544 RO
	UINT32 vcp_u0c_pic_start_hpos           :16;	//15:0	//
	UINT32 vcp_u0c_pic_start_vpos           :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U0C_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A548 RO
	UINT32 vcp_u1y_pic_init_hpos            :16;	//15:0	//
	UINT32 vcp_u1y_pic_init_vpos            :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U1Y_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A54C RO
	UINT32 vcp_u1y_pic_start_hpos           :16;	//15:0	//
	UINT32 vcp_u1y_pic_start_vpos           :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U1Y_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A550 RO
	UINT32 vcp_u1c_pic_init_hpos            :16;	//15:0	//
	UINT32 vcp_u1c_pic_init_vpos            :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U1C_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A554 RO
	UINT32 vcp_u1c_pic_start_hpos           :16;	//15:0	//
	UINT32 vcp_u1c_pic_start_vpos           :16;	//31:16	//
	};
}REG_VCP_DISP_MON_VCP_U1C_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5B8 RW
	UINT32 pg1ch_win_o_size_y               :14;	//13:0	//0x870(2160) for UD, 0x438(1080) for FHD, 0x10E0(4320) for UHD
	UINT32 resvd0                           :2;
	UINT32 pg1ch_win_o_size_x               :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_WCP_M_DISP_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5BC RW
	UINT32 lattice_pat_en                   :1;	//0 //main video 와 blending되어 출력된다.
	UINT32 resvd0                           :3;
	UINT32 ramp_pat_en                      :2;	//5:4	//"00" := bypass	"01" = diagonal	"10" = horizontal	"11" = vertical
	UINT32 mpg_o_color_sel                  :2;	//7:6	//"00" := YC	"01" = Y ONLY	"10" = C ONLY
	UINT32 border_sel                       :4;	//11:8	//"0000" := bypass	"0001" = border w/ white	"0010" = border w/ black	"0011" = border w/ red	"0100" = border w/ green	"0101" = border w/ blue
	UINT32 resvd1                           :3;
	UINT32 status_bar_en                    :1;	//15 //lm status monitor
	UINT32 resvd2                           :4;
	UINT32 status0_00_src_sel               :2;	//21:20	//"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_01_src_sel               :2;	//23:22	//"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_02_src_sel               :2;	//25:24	//"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_03_src_sel               :2;	//27:26	//"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 cg_disable                       :1;	//28 //0 : Clock gating, 1 : disable CG
	UINT32 resvd3                           :2;
	UINT32 mean_fil_en                      :1;	//31 //when 422to 444 , mean_filter_enable	0 := repeated pixel	1  = mean pixel
	};
}PE_E60_VCP_WCP_M_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5C8 RW
	UINT32 rd_pel_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//31 //
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5CC RW
	UINT32 rd_pel_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//31 //
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5D0 RW
	UINT32 even_line_cr                     :8;	//7:0	//
	UINT32 even_line_cb                     :8;	//15:8	//
	UINT32 even_line_y                      :8;	//23:16	//
	UINT32 resvd                            :7;
	UINT32 even_line_pat_en                 :1;	//31 //
	};
}PE_E60_VCP_WCP_M_LINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5D4 RW
	UINT32 odd_line_cr                      :8;	//7:0	//
	UINT32 odd_line_cb                      :8;	//15:8	//
	UINT32 odd_line_y                       :8;	//23:16	//
	UINT32 resvd                            :7;
	UINT32 odd_line_pat_en                  :1;	//31 //
	};
}PE_E60_VCP_WCP_M_LINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5E0 RW
	UINT32 rec0_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec0_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec0_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5E4 RW
	UINT32 rec0_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec0_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec0_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5E8 RW
	UINT32 rec1_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec1_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec1_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5EC RW
	UINT32 rec1_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec1_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec1_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5F0 RW
	UINT32 repeat_odd_1st_pix_y             :1;	//0 //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 홀수 일 경우 odd pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_even_1st_pix_y            :1;	//1 //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 짝수 일 경우 even pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_odd_end_pix_y             :1;	//2 //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 홀수 일 경우 even pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_even_end_pix_y            :1;	//3 //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 짝수 일 경우 odd pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_odd_1st_pix_c             :1;	//4 //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 홀수 일 경우 odd pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_even_1st_pix_c            :1;	//5 //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 짝수 일 경우 even pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_odd_end_pix_c             :1;	//6 //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 홀수 일 경우 even pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_even_end_pix_c            :1;	//7 //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 짝수 일 경우 odd pixel을 post-odd pixel로 repeat 함
	UINT32 resvd0                           :16;
	UINT32 compare_lr_diff_sel              :2;	//25:24	//
	UINT32 compare_lr_sync_sel              :1;	//26 //
	UINT32 compare_lr_mark_org_nac          :1;	//27 //
	UINT32 resvd1                           :3;
	UINT32 compare_lr_en                    :1;	//31 //
	};
}PE_E60_VCP_WCP_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5F4 RW
	UINT32 compare_lr_th_c                  :8;	//7:0	//
	UINT32 compare_lr_th_y                  :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_VCP_WCP_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5F8 RW
	UINT32 clr_nac_cr                       :4;	//3:0	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_nac_cb                       :4;	//7:4	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_nac_y                        :8;	//15:8	//we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cr                       :4;	//19:16	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_bdr_cb                       :4;	//23:20	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_bdr_y                        :8;	//31:24	//we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_E60_VCP_WCP_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A5FC RW
	UINT32 w1_clr_dark_cr                   :4;	//3:0	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w1_clr_dark_cb                   :4;	//7:4	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w1_clr_dark_y                    :8;	//15:8	//we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_cr                   :4;	//19:16	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w0_clr_dark_cb                   :4;	//23:20	//we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w0_clr_dark_y                    :8;	//31:24	//we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_E60_VCP_WCP_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A604 RW
	UINT32 set_w0_imux_ctrl                 :3;	//2:0	//"000" := vid0 (U0)	"001" = vid1 (U1)
	UINT32 set_w0_dark_en                   :1;	//3 //
	UINT32 set_w1_imux_ctrl                 :3;	//6:4	//"000" := vid0 (U0)	"001" = vid1 (U1)
	UINT32 set_w1_dark_en                   :1;	//7 //
	UINT32 cg_disable                       :1;	//8 //0 : Clock gating, 1 : disable CG  (w0,w1,a0,a1)
	UINT32 resvd0                           :7;
	UINT32 set_lparity_w0_imux_en           :1;	//16 //
	UINT32 set_lparity_w0_imux              :1;	//17 //
	UINT32 resvd1                           :2;
	UINT32 set_lparity_w1_imux_en           :1;	//20 //
	UINT32 set_lparity_w1_imux              :1;	//21 //
	UINT32 resvd2                           :2;
	UINT32 set_lparity_sync_c               :3;	//26:24	//
	UINT32 resvd3                           :1;
	UINT32 set_lparity_sync_y               :3;	//30:28	//
	UINT32 resvd4                           :1;
	};
}PE_E60_VCP_WCP_M_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A608 RW
	UINT32 set_a0_c_imux_ctrl               :3;	//2:0	//"000" := N/A	"001" = N/A
	UINT32 set_a0_c_constant_en             :1;	//3 //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 set_a1_c_imux_ctrl               :3;	//6:4	//"000" := N/A	"001" = N/A	"100" = region model alpha
	UINT32 set_a1_c_constant_en             :1;	//7 //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 resvd0                           :8;
	UINT32 set_a0_y_imux_ctrl               :3;	//18:16	//"000" := N/A	"001" = N/A
	UINT32 set_a0_y_constant_en             :1;	//19 //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 set_a1_y_imux_ctrl               :3;	//22:20	//"000" := N/A	"001" = N/A	"100" = region model alpha
	UINT32 set_a1_y_constant_en             :1;	//23 //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 resvd1                           :8;
	};
}PE_E60_VCP_WCP_M_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A60C RW
	UINT32 set_w0_abr_en                    :2;	//1:0	//"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 set_w1_abr_en                    :2;	//3:2	//"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 resvd0                           :4;
	UINT32 set_w0_awb_cr                    :1;	//8 //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_cb                    :1;	//9 //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_y                     :1;	//10 //0' := dnMiunsUp	'1' = dn
	UINT32 resvd1                           :1;
	UINT32 set_w1_awb_cr                    :1;	//12 //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_cb                    :1;	//13 //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_y                     :1;	//14 //0' := dnMiunsUp	'1' = dn
	UINT32 resvd2                           :8;
	UINT32 w1_clr_alpha_nac_en              :1;	//23 //
	UINT32 w1_clr_alpha_nac                 :8;	//31:24	//
	};
}PE_E60_VCP_WCP_M_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A610 RW
	UINT32 w0_clr_alpha                     :8;	//7:0	//0x00 : DN (non active clolor)	0xFF : UP (Window 0)
	UINT32 w1_clr_alpha                     :8;	//15:8	//0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 resvd                            :16;
	};
}PE_E60_VCP_WCP_M_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A614 RW
	UINT32 set_ha_o_mux_ctrl                :4;	//3:0	//"0000" := display hactive	"0001" = w0 hactive	"0010" = w1 hactive
	UINT32 set_va_o_mux_ctrl                :4;	//7:4	//"0000" := display vactive	"0001" = w0 vactive	"0010" = w1 vactive
	UINT32 set_de_o_mux_ctrl                :4;	//11:8	//DE processing for SOSD ONLY	"0000" := display de	"0001" = w0_va&w0_ha	"0010" = w1_va&w1_ha	"0101" = (w0_va&w0_ha) | (w1_va&w1_ha)	"1000" = ~(w0_va&w0_ha)	"1001" = ~(w1_va&w1_ha)	"1100" = ~((w0_va&w0_ha) | (w1_va&w1_ha))
	UINT32 resvd                            :20;
	};
}PE_E60_VCP_WCP_M_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A618 RW
	UINT32 set_pic_init_y_mux_m_wcp         :4;	//3:0	//"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_m_wcp        :4;	//7:4	//"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 set_pic_init_c_mux_m_wcp         :4;	//11:8	//"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_m_wcp        :4;	//15:12	//"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 resvd                            :16;
	};
}PE_E60_VCP_WCP_M_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A640 RO
	UINT32 msb8_rd_pel_cr                   :8;	//7:0	//
	UINT32 msb8_rd_pel_cb                   :8;	//15:8	//
	UINT32 msb8_rd_pel_y                    :8;	//23:16	//
	UINT32 lsb2_rd_pel_cr                   :2;	//25:24	//
	UINT32 lsb2_rd_pel_cb                   :2;	//27:26	//
	UINT32 lsb2_rd_pel_y                    :2;	//29:28	//
	UINT32 resvd                            :2;
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A644 RO
	UINT32 msb8_rd_pel_cr                   :8;
	UINT32 msb8_rd_pel_cb                   :8;	//15:8	//
	UINT32 msb8_rd_pel_y                    :8;	//23:16	//
	UINT32 lsb2_rd_pel_cr                   :2;	//25:24	//
	UINT32 lsb2_rd_pel_cb                   :2;	//27:26	//
	UINT32 lsb2_rd_pel_y                    :2;	//29:28	//
	UINT32 resvd1                           :2;
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A648 RO
	UINT32 msb8_rd_pel_cr                   :8;	//7:0	//
	UINT32 msb8_rd_pel_cb                   :8;	//15:8	//
	UINT32 msb8_rd_pel_y                    :8;	//23:16	//
	UINT32 lsb2_rd_pel_cr                   :2;	//25:24	//
	UINT32 lsb2_rd_pel_cb                   :2;	//27:26	//
	UINT32 lsb2_rd_pel_y                    :2;	//29:28	//
	UINT32 resvd                            :2;
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A64C RO
	UINT32 msb8_rd_pel_cr                   :8;	//7:0	//
	UINT32 msb8_rd_pel_cb                   :8;	//15:8	//
	UINT32 msb8_rd_pel_y                    :8;	//23:16	//
	UINT32 lsb2_rd_pel_cr                   :2;	//25:24	//
	UINT32 lsb2_rd_pel_cb                   :2;	//27:26	//
	UINT32 lsb2_rd_pel_y                    :2;	//29:28	//
	UINT32 resvd                            :2;
	};
}PE_E60_VCP_WCP_M_PIXEL_READ_DATA_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A660 RW
	UINT32 win_pos_y0_auto                  :14;	//13:0	//Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//28:16	//X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A664 RW
	UINT32 win_size_y_auto                  :14;	//13:0	//Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//28:16	//X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//30 //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//31 //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_E60_VCP_SG_BDR_V0_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A668 RW
	UINT32 win_pos_y0_auto                  :14;	//13:0	//Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//28:16	//X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A66C RW
	UINT32 win_size_y_auto                  :14;	//13:0	//Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//28:16	//X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//30 //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//31 //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_E60_VCP_SG_BDR_V1_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A680 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A684 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A688 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A690 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A694 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A698 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6A0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_2_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6A4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_2_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6A8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_2_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6B0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_3_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6B4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_3_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6B8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_3_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6C0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6C4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6C8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6D0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6D4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6D8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6E0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_2_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6E4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_2_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6E8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_2_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6F0 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_3_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6F4 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_3_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A6F8 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_3_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A700 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_4_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A704 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_4_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A708 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_4_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A710 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_5_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A714 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_5_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A718 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_5_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A720 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_6_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A724 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_6_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A728 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_6_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A730 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_7_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A734 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V0_7_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A738 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V0_7_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A740 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_4_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A744 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_4_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A748 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_4_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A750 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_5_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A754 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_5_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A758 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_5_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A760 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_6_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A764 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_6_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A768 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_6_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A770 RW
	UINT32 win_pos_y0                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_7_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A774 RW
	UINT32 win_pos_y1                       :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_SG_BDR_V1_7_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A778 RW
	UINT32 sync_ha_sub_sel                  :1;	//0 //
	UINT32 sync_ha_sub_en                   :1;	//1 //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//5:4	//"11" = 4-ch	"10" := 8-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//19:16	//
	UINT32 win_border_width_left            :4;	//23:20	//
	UINT32 win_border_width_down            :4;	//27:24	//
	UINT32 win_border_width_up              :4;	//31:28	//
	};
}PE_E60_VCP_SG_BDR_V1_7_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A780 RW
	UINT32 rec5_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec5_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec5_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC5_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A784 RW
	UINT32 rec5_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec5_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec5_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC5_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A788 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC5_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A78C RW
	UINT32 rec6_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec6_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec6_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC6_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A790 RW
	UINT32 rec6_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec6_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec6_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC6_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A794 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC6_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A798 RW
	UINT32 rec7_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec7_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec7_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC7_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A79C RW
	UINT32 rec7_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec7_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec7_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC7_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7A0 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC7_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7A4 RW
	UINT32 rec8_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec8_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec8_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC8_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7A8 RW
	UINT32 rec8_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec8_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec8_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC8_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7AC RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC8_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7B0 RW
	UINT32 rec9_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec9_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec9_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC9_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7B4 RW
	UINT32 rec9_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec9_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec9_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC9_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7B8 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC9_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A7C4 RW
	UINT32 set_pic_init_y_mux_ms_wcp        :4;	//3:0	//"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_ms_wcp       :4;	//7:4	//"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 set_pic_init_c_mux_ms_wcp        :4;	//11:8	//"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_ms_wcp       :4;	//15:12	//"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 resvd                            :16;
	};
}PE_E60_VCP_WCP_MS_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A800 RW
	UINT32 resvd0                           :4;
	UINT32 set_region_m_y_sync_sel          :2;	//5:4	//0' : = main display sync	'1' = sub display sync
	UINT32 set_region_m_c_sync_sel          :2;	//7:6	//0' : = main display sync	'1' = sub display sync
	UINT32 resvd1                           :23;
	UINT32 alpha_gen_disable                :1;	//31 //
	};
}PE_E60_VCP_WCP_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A804 RW
	UINT32 set_vsize                        :16;	//15:0	//vsize
	UINT32 set_hsize                        :16;	//31:16	//hsize
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A808 RW
	UINT32 region_shape                     :2;	//1:0	//"0" = rect	"1" = line	"2" = ellipse
	UINT32 alpha_inversion_y                :1;	//2 //"0" = normal	"1" = alpha inversion
	UINT32 rm_op_mode                       :2;	//4:3	//0: 1-Ch., 1: 2-Ch (e/o)., 2: 4-Ch. (e0/o0/e1/o1)
	UINT32 rm_enable                        :1;	//5 //
	UINT32 ellipse_ez_set                   :1;	//6 //
	UINT32 rm_yc_same_align                 :1;	//7 //
	UINT32 resvd                            :8;
	UINT32 alpha_1                          :8;	//23:16	//alpha 1
	UINT32 alpha_0                          :8;	//31:24	//alpha 0
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A80C RW
	UINT32 y0_a_q                           :16;	//15:0	//(RECT) y0	(LINE) a of by-a(x-tx)-c=0 [11:0]	(ELLIPSE) q of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1
	UINT32 x0_p                             :16;	//31:16	//(RECT) x0	(ELLIPSE) p of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A810 RW
	UINT32 x1_y1_tx_pp                      :32;	//31:0	//(RECT) x1 [31:16]	(RECT) y1 [15:0]	(LINE) tx of by-a(x-tx)-c=0 [12:0]	(ELLIPSE) p^2 of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [21:0]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A814 RW
	UINT32 b_c_qq                           :32;	//31:0	//(RECT) reserved	(LINE) b of by-a(x-tx)-c=0 [16]	(LINE) c of by-a(x-tx)-c=0 [15:0]	(ELLIPSE) q^2 of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [21:0]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A818 RW
	UINT32 dy                               :16;	//15:0	//(RECT) reserved	(LINE) reserved	(ELLIPSE) dy of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [15:0]
	UINT32 dx                               :16;	//31:16	//(RECT) reserved	(LINE) reserved	(ELLIPSE) dx of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [31:16]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_Y_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A81C RW
	UINT32 set_vsize                        :16;	//15:0	//vsize
	UINT32 set_hsize                        :16;	//31:16	//hsize
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A820 RW
	UINT32 region_shape                     :2;	//1:0	//"0" = rect	"1" = line	"2" = ellipse
	UINT32 alpha_inversion_c                :1;	//2 //"0" = normal	"1" = alpha inversion
	UINT32 eo_mode_en                       :1;	//3 //Even/Odd mode enable
	UINT32 resvd                            :12;
	UINT32 alpha_1                          :8;	//23:16	//alpha 1
	UINT32 alpha_0                          :8;	//31:24	//alpha 0
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A824 RW
	UINT32 y0_a_q                           :16;	//15:0	//(RECT) y0	(LINE) a of by-a(x-tx)-c=0 [11:0]	(ELLIPSE) q of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1
	UINT32 x0_p                             :16;	//31:16	//(RECT) x0	(ELLIPSE) p of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A828 RW
	UINT32 x1_y1_tx_pp                      :32;	//31:0	//(RECT) x1 [31:16]	(RECT) y1 [15:0]	(LINE) tx of by-a(x-tx)-c=0 [12:0]	(ELLIPSE) p^2 of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [21:0]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A82C RW
	UINT32 b_c_qq                           :32;	//31:0	//(RECT) reserved	(LINE) b of by-a(x-tx)-c=0 [16]	(LINE) c of by-a(x-tx)-c=0 [15:0]	(ELLIPSE) q^2 of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [21:0]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A830 RW
	UINT32 dy                               :16;	//15:0	//(RECT) reserved	(LINE) reserved	(ELLIPSE) dy of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [15:0]
	UINT32 dx                               :16;	//31:16	//(RECT) reserved	(LINE) reserved	(ELLIPSE) dx of (x-dx)^2/p^2 + (y-dy)^2/q^2 = 1 [31:16]
	};
}PE_E60_VCP_WCP_ALPHA_GEN_C_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A834 RW
	UINT32 rec2_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec2_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec2_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC2_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A838 RW
	UINT32 rec2_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec2_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec2_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC2_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A83C RW
	UINT32 rec3_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec3_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec3_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A840 RW
	UINT32 rec3_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec3_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec3_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A844 RW
	UINT32 rec4_e_pos_x                     :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 rec4_s_pos_x                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 rec4_en                          :1;	//31 //line draw
	};
}PE_E60_VCP_WCP_M_REC4_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A848 RW
	UINT32 rec4_e_pos_y                     :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 rec4_s_pos_y                     :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 rec4_fill_en                     :1;	//31 //box fill
	};
}PE_E60_VCP_WCP_M_REC4_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A84C RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC0_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A850 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC1_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A854 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A858 RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC3_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A85C RW
	UINT32 clr_cr                           :8;	//7:0	//
	UINT32 clr_cb                           :8;	//15:8	//
	UINT32 clr_y                            :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_VCP_WCP_M_REC4_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A860 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//4 //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//15:8	//
	UINT32 contrast                         :10;	//25:16	//
	UINT32 resvd2                           :6;
	};
}PE_E60_VCP_VSP_U0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A864 RW
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//15:8	//
	UINT32 brightness                       :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VCP_VSP_U0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A868 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//15:8	//
	UINT32 contrast                         :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VCP_VSP_U1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A86C RW
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//15:8	//
	UINT32 brightness                       :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VCP_VSP_U1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A870 RW
	UINT32 crc_enable                       :1;	//0 //
	UINT32 crc_reset                        :1;	//1 //
	UINT32 resvd0                           :1;
	UINT32 auto_reset_disable               :1;	//3 //
	UINT32 vs_level                         :1;	//4 //
	UINT32 hs_level                         :1;	//5 //
	UINT32 vs_mask                          :1;	//6 //
	UINT32 hs_mask                          :1;	//7 //
	UINT32 resvd1                           :24;
	};
}PE_E60_VCP_CRC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A874 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_CRC_DATA_MASK0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A878 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_CRC_DATA_MASK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A884 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_CRC_OUT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A888 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_VCP_CRC_OUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A8A0 RW
	UINT32 h_cnt                            :16;	//15:0	//
	UINT32 v_cnt                            :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A8A4 RW
	UINT32 h_cnt                            :16;	//15:0	//
	UINT32 v_cnt                            :16;	//31:16	//
	};
}PE_E60_VCP_SG_MVC_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A8A8 RW
	UINT32 h_cnt                            :16;	//15:0	//
	UINT32 v_cnt                            :16;	//31:16	//
	};
}PE_E60_VCP_SG_SVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A8AC RW
	UINT32 h_cnt                            :16;	//15:0	//
	UINT32 v_cnt                            :16;	//31:16	//
	};
}PE_E60_VCP_SG_SVC_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A900 RW
	UINT32 vcp_mv_y_disp_intr0_mask         :1;	//0 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_mask         :1;	//1 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_mask            :1;	//2 //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_mask            :1;	//3 //vcp main display window1 vactive falling
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_y_disp_intr0_mask         :1;	//6 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_disp_intr1_mask         :1;	//7 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_w0_intr_mask            :1;	//8 //vcp sub display window0 vactive falling
	UINT32 resvd1                           :3;
	UINT32 vcp_ms_y_disp_intr_mask          :1;	//12 //
	UINT32 resvd2                           :3;
	UINT32 vcp_mv_c_disp_intr0_mask         :1;	//16 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_mask         :1;	//17 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_mask            :1;	//18 //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_mask            :1;	//19 //vcp main display window1 vactive falling
	UINT32 resvd3                           :2;
	UINT32 vcp_sv_c_disp_intr0_mask         :1;	//22 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_disp_intr1_mask         :1;	//23 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_w0_intr_mask            :1;	//24 //vcp sub display window0 vactive falling
	UINT32 resvd4                           :7;
	};
}PE_E60_VCP_DISP_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A904 RW
	UINT32 vcp_mv_y_disp_intr0_clear        :1;	//0 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_clear        :1;	//1 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_clear           :1;	//2 //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_clear           :1;	//3 //vcp main display window1 vactive falling
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_y_disp_intr0_clear        :1;	//6 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_disp_intr1_clear        :1;	//7 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_w0_intr_clear           :1;	//8 //vcp sub display window0 vactive falling
	UINT32 resvd1                           :3;
	UINT32 vcp_ms_y_disp_intr_clear         :1;	//12 //
	UINT32 resvd2                           :3;
	UINT32 vcp_mv_c_disp_intr0_clear        :1;	//16 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_clear        :1;	//17 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_clear           :1;	//18 //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_clear           :1;	//19 //vcp main display window1 vactive falling
	UINT32 resvd3                           :2;
	UINT32 vcp_sv_c_disp_intr0_clear        :1;	//22 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_disp_intr1_clear        :1;	//23 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_w0_intr_clear           :1;	//24 //vcp sub display window0 vactive falling
	UINT32 resvd4                           :7;
	};
}PE_E60_VCP_DISP_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A908 RO
	UINT32 vcp_mv_y_disp_intr0_status       :1;	//0 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_status       :1;	//1 //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_status          :1;	//2 //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_status          :1;	//3 //vcp main display window1 vactive falling
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_y_disp_intr0_status       :1;	//6 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_disp_intr1_status       :1;	//7 //vcp sub display vsync variable position control
	UINT32 vcp_sv_y_w0_intr_status          :1;	//8 //vcp sub display window0 vactive falling
	UINT32 resvd1                           :3;
	UINT32 vcp_ms_y_disp_intr_status        :1;	//12 //
	UINT32 resvd2                           :3;
	UINT32 vcp_mv_c_disp_intr0_status       :1;	//16 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_status       :1;	//17 //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_status          :1;	//18 //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_status          :1;	//19 //vcp main display window1 vactive falling
	UINT32 resvd3                           :2;
	UINT32 vcp_sv_c_disp_intr0_status       :1;	//22 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_disp_intr1_status       :1;	//23 //vcp sub display vsync variable position control
	UINT32 vcp_sv_c_w0_intr_status          :1;	//24 //vcp sub display window0 vactive falling
	UINT32 resvd4                           :7;
	};
}PE_E60_VCP_DISP_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A90C RW
	UINT32 vcp_mv_disp_intr0_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_mv_disp_intr0_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR0_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A910 RW
	UINT32 vcp_mv_disp_intr1_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_mv_disp_intr1_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR1_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A914 RW
	UINT32 vcp_mv_disp_intr0_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_mv_disp_intr0_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR0_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A918 RW
	UINT32 vcp_mv_disp_intr1_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_mv_disp_intr1_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR1_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A91C RW
	UINT32 vcp_sv_disp_intr0_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_sv_disp_intr0_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR0_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A920 RW
	UINT32 vcp_sv_disp_intr1_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_sv_disp_intr1_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR1_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A924 RW
	UINT32 vcp_sv_disp_intr0_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_sv_disp_intr0_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR0_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A928 RW
	UINT32 vcp_sv_disp_intr1_pos_x          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 vcp_sv_disp_intr1_pos_y          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VCP_DISP_INTR1_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A92C RW
	UINT32 vcp_intr_mv_y_v_src              :1;	//0 //0' := vsync	'1' = vactive
	UINT32 vcp_intr_mv_y_h_src              :1;	//1 //0' := hsync	'1' = hactive
	UINT32 resvd0                           :1;
	UINT32 vcp_intr_mv_y_enable             :1;	//3 //
	UINT32 vcp_intr_mv_c_v_src              :1;	//4 //0' := vsync	'1' = vactive
	UINT32 vcp_intr_mv_c_h_src              :1;	//5 //0' := hsync	'1' = hactive
	UINT32 resvd1                           :1;
	UINT32 vcp_intr_mv_c_enable             :1;	//7 //
	UINT32 vcp_intr_sv_y_v_src              :1;	//8 //0' := vsync	'1' = vactive
	UINT32 vcp_intr_sv_y_h_src              :1;	//9 //0' := hsync	'1' = hactive
	UINT32 resvd2                           :1;
	UINT32 vcp_intr_sv_y_enable             :1;	//11 //
	UINT32 vcp_intr_sv_c_v_src              :1;	//12 //0' := vsync	'1' = vactive
	UINT32 vcp_intr_sv_c_h_src              :1;	//13 //0' := hsync	'1' = hactive
	UINT32 resvd3                           :1;
	UINT32 vcp_intr_sv_c_enable             :1;	//15 //
	UINT32 resvd4                           :16;
	};
}PE_E60_VCP_DISP_INTR_SRC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A930 RW
	UINT32 resvd0                           :3;
	UINT32 vcp_422_mean_filter_en           :1;	//3 //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//4 //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v0_param_size
	UINT32 vcp_csc_debug_mode               :5;	//9:5	//for debug
	UINT32 vcp_422_mean_filter_last_pixel   :11;	//20:10	//size of mean filter	real size 7680/4 => 1920 setting size
	UINT32 resvd1                           :11;
	};
}PE_E60_VCP_U0_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A934 RW
	UINT32 vcp_csc_coefficient1             :15;	//14:0	//
	UINT32 vcp_csc_debug_mode1              :1;	//15 //for debug
	UINT32 vcp_csc_coefficient0             :15;	//30:16	//
	UINT32 vcp_csc_debug_mode0              :1;	//31 //for debug
	};
}PE_E60_VCP_U1_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A938 RW
	UINT32 vcp_csc_coefficient3             :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient2             :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VCP_U1_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A93C RW
	UINT32 vcp_csc_coefficient5             :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient4             :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VCP_U1_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A940 RW
	UINT32 vcp_csc_coefficient7             :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient6             :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VCP_U1_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A944 RW
	UINT32 vcp_csc_offset0                  :11;	//10:0	//Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_coefficient8             :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VCP_U1_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A948 RW
	UINT32 vcp_csc_offset2                  :11;	//10:0	//Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset1                  :11;	//26:16	//Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_E60_VCP_U1_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A94C RW
	UINT32 vcp_csc_offset4                  :11;	//10:0	//Post add offset y	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset3                  :11;	//26:16	//Post add offset x	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_E60_VCP_U1_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A950 RW
	UINT32 vcp_csc_coeff_load               :1;	//0 //this bit is auto cleared
	UINT32 vcp_csc_en                       :1;	//1 //csc enable
	UINT32 vcp_csc_pcg_off                  :1;	//2 //power clock gating off
	UINT32 vcp_422_mean_filter_en           :1;	//3 //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//4 //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v1_param_size
	UINT32 vcp_csc_debug_mode               :5;	//9:5	//for debug
	UINT32 vcp_422_mean_filter_last_pixel   :11;	//20:10	//size of mean filter	real size 7680/4 => 1920 setting size
	UINT32 vcp_csc_offset5                  :11;	//31:21	//Post add offset z	Range -1024~1023
	};
}PE_E60_VCP_U1_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902A954 RW
	UINT32 vcp_active_line_cnt_en           :1;	//0 //0 : disable	1 : enable
	UINT32 vcp_cnt_ref                      :1;	//1 //0 : vsync rising	1 : vsync falling
	UINT32 vcp_active_line_cnt              :15;	//16:2	//
	UINT32 resvd                            :15;
	};
}PE_E60_VCP_ACTIVE_LINE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA60 RW
	UINT32 reg_motion_gain_pic_rptr_man     :2;	//1:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_motion_gain_pic_rptr_man_en  :1;	//3:3	//
	UINT32 reg_motion_gain_pic_wptr_man     :2;	//5:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_motion_gain_pic_wptr_man_en  :1;	//7:7	//
	UINT32 reg_motion_gain_pic_data_man     :2;	//9:8	//0: test data off	1: 128	2: gradient	3: horizontal box
	UINT32 reg_motion_gain_pic_rptr_on      :1;	//10:10	//
	UINT32 reg_motion_gain_pic_wptr_on      :1;	//11:11	//
	UINT32 reg_motion_gain_pic_wd_man       :4;	//15:12	//x16, {reg_pic_wd_man,4'd0}
	UINT32 reg_motion_gain_pic_wd_man_on    :1;	//16:16	//
	UINT32 reg_motion_gain_pic_rd_lsb_man   :2;	//18:17	//0: [1:0] = 0	1: [1:0] = 3	2: [1:0] = [3:2]	3: [1:0] = [9:8]
	UINT32 reg_motion_gain_ro_buf_wrcnt     :10;	//28:19	//
	UINT32 reg_motion_gain_ro_buf_wrsel     :1;	//29:29	//
	UINT32 resvd2                           :2;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA64 RW
	UINT32 reg_motion_gain_in_hoffset       :13;	//12:0	//input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_voffset       :13;	//28:16	//input window offset
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA68 RW
	UINT32 reg_motion_gain_in_hactive       :13;	//12:0	//input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vactive       :13;	//28:16	//input window active size
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA6C RW
	UINT32 reg_motion_gain_in_hsize         :13;	//12:0	//input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_in_vsize         :13;	//28:16	//input source total size
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA70 RW
	UINT32 reg_motion_gain_out_pic_width    :13;	//12:0	//width (default: 3840/2)
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_out_pic_height   :13;	//28:16	//height (default: 4320)
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA74 RW
	UINT32 reg_motion_gain_phase_off_h      :9;	//8:0	//vertical offset of initial pixel position (signed value)  	min: -255	max: +255
	UINT32 resvd0                           :7;
	UINT32 reg_motion_gain_phase_off_v      :9;	//24:16	//horizontal offset of initial pixel position (signed value)  	min: -255	max: +255
	UINT32 resvd1                           :2;
	UINT32 reg_vsc_1to2_last_sel            :1;	//27:27	//0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//28:28	//0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//29:29	//'0' : 256p	     '1' : 32p
	UINT32 reg_motion_gain_sampling_mode    :2;	//31:30	//0: normal-auto	1: manual-set
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA78 RW
	UINT32 reg_motion_gain_numerator_h      :13;	//12:0	//120=4*30
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_numerator_v      :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA7C RW
	UINT32 reg_motion_gain_denominator_h    :13;	//12:0	//(default: 1920(3840/2))
	UINT32 resvd0                           :3;
	UINT32 reg_motion_gain_denominator_v    :13;	//28:16	//(default: 4320)
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA80 RW
	UINT32 reg_motion_gain_win0_en          :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_motion_gain_win1_en          :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_motion_gain_win01_en         :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_motion_gain_win_outside      :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_motion_gain_win_en           :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_motion_gain_bdr_alpha        :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_motion_gain_bdr_wid          :2;	//14:13	//border width
	UINT32 reg_motion_gain_bdr_en           :1;	//15:15	//border enable
	UINT32 reg_motion_gain_cr5              :5;	//20:16	//border color : cr5
	UINT32 reg_motion_gain_cb5              :5;	//25:21	//border color : cb5
	UINT32 reg_motion_gain_yy6              :6;	//31:26	//border color : yy6
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA84 RW
	UINT32 reg_motion_gain_win_w0_x0        :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y0        :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA88 RW
	UINT32 reg_motion_gain_win_w0_x1        :12;	//11:0	//win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :4;
	UINT32 reg_motion_gain_win_w0_y1        :13;	//28:16	//win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA8C RW
	UINT32 reg_motion_gain_out_hoffset      :13;	//12:0	//output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//15:13	//4p hoffset
	UINT32 reg_motion_gain_out_voffset      :13;	//28:16	//output window offset
	UINT32 resvd                            :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA90 RW
	UINT32 reg_motion_gain_out_hactive      :13;	//12:0	//output window active size : 1920(7680/4)
	UINT32 reg_out_havg_4x_mode             :3;	//15:13	//0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_motion_gain_out_vactive      :13;	//28:16	//output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//29:29	//0 : 0	1 : last pixel repeat
	UINT32 logo_l7sc_out_sel                :2;	//31:30	//0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA94 RW
	UINT32 reg_mode_444                     :1;	//0:0	//Set Accoding to VSD1_SHP.Core_ctrl.reg_top_mode_444	0: 422 mode	1: 444 mode
	UINT32 reg_flick_motion_sel             :2;	//2:1	//Set Accoding to VSD1_SHP.SHP_FRC_FLICK_CTRL_00.reg_flick_motion_sel	SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd                            :29;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA98 RW
	UINT32 shp_motion_gain_ctrl_14          :32;	//31:0	//
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AA9C RW
	UINT32 shp_motion_gain_ctrl_15          :32;	//31:0	//
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AAA0 R
	UINT32 ibuf_logo_gain_vcnt              :9;	//8:0	//
	UINT32 resvd                            :23;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902AAA4 R
	UINT32 current_out_line                 :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 current_in_line                  :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}REG_VCP_DISP_SHP_MOTION_GAIN_STAT_01_T;

typedef struct {
	PE_E60_VCP_DISP_CTRL0_T                        vcp_disp_ctrl0;	//0xC902A400
	PE_E60_VCP_DISP_CTRL1_T                        vcp_disp_ctrl1;	//0xC902A404
	PE_E60_VCP_DISP_CTRL2_T                        vcp_disp_ctrl2;	//0xC902A408
	PE_E60_VCP_DISP_CTRL3_T                        vcp_disp_ctrl3;	//0xC902A40C
	PE_E60_VCP_CDC_MV_SYNC_CTRL_T            vcp_cdc_mv_sync_ctrl;	//0xC902A410
	PE_E60_VCP_CDC_MV_RST_CTRL_T              vcp_cdc_mv_rst_ctrl;	//0xC902A414
	PE_E60_VCP_420_CTRL_T                            vcp_420_ctrl;	//0xC902A418
	UINT32                                                    reserved0;	//0xC902A41C
	PE_E60_VCP_U0_WIN_O_POS_T                    vcp_u0_win_o_pos;	//0xC902A420
	PE_E60_VCP_U0_WIN_O_SIZE_T                  vcp_u0_win_o_size;	//0xC902A424
	PE_E60_VCP_U0_PG_PAT_CTRL_T                vcp_u0_pg_pat_ctrl;	//0xC902A428
	PE_E60_VCP_U0_PG_PEAK_SIZE_T              vcp_u0_pg_peak_size;	//0xC902A42C
	PE_E60_VCP_U0_CDC_Y_CTRL0_T                vcp_u0_cdc_y_ctrl0;	//0xC902A430
	PE_E60_VCP_U0_CDC_Y_CTRL1_T                vcp_u0_cdc_y_ctrl1;	//0xC902A434
	PE_E60_VCP_U0_CDC_Y_CTRL2_T                vcp_u0_cdc_y_ctrl2;	//0xC902A438
	PE_E60_VCP_U0_CDC_Y_STATUS_T              vcp_u0_cdc_y_status;	//0xC902A43C
	PE_E60_VCP_U0_CDC_C_CTRL0_T                vcp_u0_cdc_c_ctrl0;	//0xC902A440
	PE_E60_VCP_U0_CDC_C_CTRL1_T                vcp_u0_cdc_c_ctrl1;	//0xC902A444
	PE_E60_VCP_U0_CDC_C_CTRL2_T                vcp_u0_cdc_c_ctrl2;	//0xC902A448
	PE_E60_VCP_U0_CDC_C_STATUS_T              vcp_u0_cdc_c_status;	//0xC902A44C
	PE_E60_VCP_U1_WIN_O_POS_T                    vcp_u1_win_o_pos;	//0xC902A450
	PE_E60_VCP_U1_WIN_O_SIZE_T                  vcp_u1_win_o_size;	//0xC902A454
	PE_E60_VCP_U1_PG_PAT_CTRL_T                vcp_u1_pg_pat_ctrl;	//0xC902A458
	PE_E60_VCP_U1_PG_PEAK_SIZE_T              vcp_u1_pg_peak_size;	//0xC902A45C
	PE_E60_VCP_U1_CDC_Y_CTRL0_T                vcp_u1_cdc_y_ctrl0;	//0xC902A460
	PE_E60_VCP_U1_CDC_Y_CTRL1_T                vcp_u1_cdc_y_ctrl1;	//0xC902A464
	PE_E60_VCP_U1_CDC_Y_CTRL2_T                vcp_u1_cdc_y_ctrl2;	//0xC902A468
	PE_E60_VCP_U1_CDC_Y_STATUS_T              vcp_u1_cdc_y_status;	//0xC902A46C
	PE_E60_VCP_U1_CDC_C_CTRL0_T                vcp_u1_cdc_c_ctrl0;	//0xC902A470
	PE_E60_VCP_U1_CDC_C_CTRL1_T                vcp_u1_cdc_c_ctrl1;	//0xC902A474
	PE_E60_VCP_U1_CDC_C_CTRL2_T                vcp_u1_cdc_c_ctrl2;	//0xC902A478
	PE_E60_VCP_U1_CDC_C_STATUS_T              vcp_u1_cdc_c_status;	//0xC902A47C
	PE_E60_VCP_U0_WIN_O_POS_AUX_T            vcp_u0_win_o_pos_aux;	//0xC902A480
	PE_E60_VCP_U0_WIN_O_SIZE_AUX_T          vcp_u0_win_o_size_aux;	//0xC902A484
	PE_E60_VCP_U1_WIN_O_POS_AUX_T            vcp_u1_win_o_pos_aux;	//0xC902A488
	PE_E60_VCP_U1_WIN_O_SIZE_AUX_T          vcp_u1_win_o_size_aux;	//0xC902A48C
	UINT32                                                    reserved1;	//0xC902A490
	UINT32                                                    reserved2;	//0xC902A494
	UINT32                                                    reserved3;	//0xC902A498
	UINT32                                                    reserved4;	//0xC902A49C
	UINT32                                                    reserved5;	//0xC902A4A0
	UINT32                                                    reserved6;	//0xC902A4A4
	UINT32                                                    reserved7;	//0xC902A4A8
	UINT32                                                    reserved8;	//0xC902A4AC
	UINT32                                                    reserved9;	//0xC902A4B0
	UINT32                                                   reserved10;	//0xC902A4B4
	UINT32                                                   reserved11;	//0xC902A4B8
	UINT32                                                   reserved12;	//0xC902A4BC
	UINT32                                                   reserved13;	//0xC902A4C0
	UINT32                                                   reserved14;	//0xC902A4C4
	UINT32                                                   reserved15;	//0xC902A4C8
	UINT32                                                   reserved16;	//0xC902A4CC
	UINT32                                                   reserved17;	//0xC902A4D0
	UINT32                                                   reserved18;	//0xC902A4D4
	UINT32                                                   reserved19;	//0xC902A4D8
	UINT32                                                   reserved20;	//0xC902A4DC
	PE_E60_VCP_SG_MVY_CTRL_0_T                  vcp_sg_mvy_ctrl_0;	//0xC902A4E0
	PE_E60_VCP_SG_MVY_CTRL_1_T                  vcp_sg_mvy_ctrl_1;	//0xC902A4E4
	PE_E60_VCP_SG_MVY_CTRL_2_T                  vcp_sg_mvy_ctrl_2;	//0xC902A4E8
	PE_E60_VCP_SG_MVY_CTRL_3_T                  vcp_sg_mvy_ctrl_3;	//0xC902A4EC
	PE_E60_VCP_SG_MVY_CTRL_4_T                  vcp_sg_mvy_ctrl_4;	//0xC902A4F0
	PE_E60_VCP_SG_MVY_CTRL_5_T                  vcp_sg_mvy_ctrl_5;	//0xC902A4F4
	PE_E60_VCP_SG_MVY_CTRL_6_T                  vcp_sg_mvy_ctrl_6;	//0xC902A4F8
	PE_E60_VCP_SG_MVY_CTRL_7_T                  vcp_sg_mvy_ctrl_7;	//0xC902A4FC
	PE_E60_VCP_SG_MVY_CTRL_8_T                  vcp_sg_mvy_ctrl_8;	//0xC902A500
	PE_E60_VCP_SG_MVY_CTRL_9_T                  vcp_sg_mvy_ctrl_9;	//0xC902A504
	UINT32                                                   reserved21;	//0xC902A508
	UINT32                                                   reserved22;	//0xC902A50C
	PE_E60_VCP_SG_MVC_CTRL_0_T                  vcp_sg_mvc_ctrl_0;	//0xC902A510
	PE_E60_VCP_SG_MVC_CTRL_1_T                  vcp_sg_mvc_ctrl_1;	//0xC902A514
	PE_E60_VCP_SG_MVC_CTRL_2_T                  vcp_sg_mvc_ctrl_2;	//0xC902A518
	PE_E60_VCP_SG_MVC_CTRL_3_T                  vcp_sg_mvc_ctrl_3;	//0xC902A51C
	PE_E60_VCP_SG_MVC_CTRL_4_T                  vcp_sg_mvc_ctrl_4;	//0xC902A520
	PE_E60_VCP_SG_MVC_CTRL_5_T                  vcp_sg_mvc_ctrl_5;	//0xC902A524
	PE_E60_VCP_SG_MVC_CTRL_6_T                  vcp_sg_mvc_ctrl_6;	//0xC902A528
	PE_E60_VCP_SG_MVC_CTRL_7_T                  vcp_sg_mvc_ctrl_7;	//0xC902A52C
	PE_E60_VCP_SG_MVC_CTRL_8_T                  vcp_sg_mvc_ctrl_8;	//0xC902A530
	PE_E60_VCP_SG_MVC_CTRL_9_T                  vcp_sg_mvc_ctrl_9;	//0xC902A534
	REG_VCP_DISP_MON_VCP_U0Y_PIC_INIT_POS_T    mon_vcp_u0y_pic_init_pos;	//0xC902A538
	REG_VCP_DISP_MON_VCP_U0Y_PIC_START_POS_T  mon_vcp_u0y_pic_start_pos;	//0xC902A53C
	REG_VCP_DISP_MON_VCP_U0C_PIC_INIT_POS_T    mon_vcp_u0c_pic_init_pos;	//0xC902A540
	REG_VCP_DISP_MON_VCP_U0C_PIC_START_POS_T  mon_vcp_u0c_pic_start_pos;	//0xC902A544
	REG_VCP_DISP_MON_VCP_U1Y_PIC_INIT_POS_T    mon_vcp_u1y_pic_init_pos;	//0xC902A548
	REG_VCP_DISP_MON_VCP_U1Y_PIC_START_POS_T  mon_vcp_u1y_pic_start_pos;	//0xC902A54C
	REG_VCP_DISP_MON_VCP_U1C_PIC_INIT_POS_T    mon_vcp_u1c_pic_init_pos;	//0xC902A550
	REG_VCP_DISP_MON_VCP_U1C_PIC_START_POS_T  mon_vcp_u1c_pic_start_pos;	//0xC902A554
	UINT32                                                   reserved23;	//0xC902A558
	UINT32                                                   reserved24;	//0xC902A55C
	UINT32                                                   reserved25;	//0xC902A560
	UINT32                                                   reserved26;	//0xC902A564
	UINT32                                                   reserved27;	//0xC902A568
	UINT32                                                   reserved28;	//0xC902A56C
	UINT32                                                   reserved29;	//0xC902A570
	UINT32                                                   reserved30;	//0xC902A574
	UINT32                                                   reserved31;	//0xC902A578
	UINT32                                                   reserved32;	//0xC902A57C
	UINT32                                                   reserved33;	//0xC902A580
	UINT32                                                   reserved34;	//0xC902A584
	UINT32                                                   reserved35;	//0xC902A588
	UINT32                                                   reserved36;	//0xC902A58C
	UINT32                                                   reserved37;	//0xC902A590
	UINT32                                                   reserved38;	//0xC902A594
	UINT32                                                   reserved39;	//0xC902A598
	UINT32                                                   reserved40;	//0xC902A59C
	UINT32                                                   reserved41;	//0xC902A5A0
	UINT32                                                   reserved42;	//0xC902A5A4
	UINT32                                                   reserved43;	//0xC902A5A8
	UINT32                                                   reserved44;	//0xC902A5AC
	UINT32                                                   reserved45;	//0xC902A5B0
	UINT32                                                   reserved46;	//0xC902A5B4
	PE_E60_VCP_WCP_M_DISP_SIZE_T              vcp_wcp_m_disp_size;	//0xC902A5B8
	PE_E60_VCP_WCP_M_PG_PAT_CTRL_T          vcp_wcp_m_pg_pat_ctrl;	//0xC902A5BC
	UINT32                                                   reserved47;	//0xC902A5C0
	UINT32                                                   reserved48;	//0xC902A5C4
	PE_E60_VCP_WCP_M_PIXEL_READ_CTRL_T  vcp_wcp_m_pixel_read_ctrl;	//0xC902A5C8
	PE_E60_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T vcp_wcp_m_pixel_read_ctrl_aux;	//0xC902A5CC
	PE_E60_VCP_WCP_M_LINE_CTRL0_T            vcp_wcp_m_line_ctrl0;	//0xC902A5D0
	PE_E60_VCP_WCP_M_LINE_CTRL1_T            vcp_wcp_m_line_ctrl1;	//0xC902A5D4
	UINT32                                                   reserved49;	//0xC902A5D8
	UINT32                                                   reserved50;	//0xC902A5DC
	PE_E60_VCP_WCP_M_REC0_POS_X_T            vcp_wcp_m_rec0_pos_x;	//0xC902A5E0
	PE_E60_VCP_WCP_M_REC0_POS_Y_T            vcp_wcp_m_rec0_pos_y;	//0xC902A5E4
	PE_E60_VCP_WCP_M_REC1_POS_X_T            vcp_wcp_m_rec1_pos_x;	//0xC902A5E8
	PE_E60_VCP_WCP_M_REC1_POS_Y_T            vcp_wcp_m_rec1_pos_y;	//0xC902A5EC
	PE_E60_VCP_WCP_M_CTRL_0_T                    vcp_wcp_m_ctrl_0;	//0xC902A5F0
	PE_E60_VCP_WCP_M_CTRL_1_T                    vcp_wcp_m_ctrl_1;	//0xC902A5F4
	PE_E60_VCP_WCP_M_CTRL_2_T                    vcp_wcp_m_ctrl_2;	//0xC902A5F8
	PE_E60_VCP_WCP_M_CTRL_3_T                    vcp_wcp_m_ctrl_3;	//0xC902A5FC
	UINT32                                                   reserved51;	//0xC902A600
	PE_E60_VCP_WCP_M_CTRL_5_T                    vcp_wcp_m_ctrl_5;	//0xC902A604
	PE_E60_VCP_WCP_M_CTRL_6_T                    vcp_wcp_m_ctrl_6;	//0xC902A608
	PE_E60_VCP_WCP_M_CTRL_7_T                    vcp_wcp_m_ctrl_7;	//0xC902A60C
	PE_E60_VCP_WCP_M_CTRL_8_T                    vcp_wcp_m_ctrl_8;	//0xC902A610
	PE_E60_VCP_WCP_M_CTRL_9_T                    vcp_wcp_m_ctrl_9;	//0xC902A614
	PE_E60_VCP_WCP_M_CTRL_10_T                  vcp_wcp_m_ctrl_10;	//0xC902A618
	UINT32                                                   reserved52;	//0xC902A61C
	UINT32                                                   reserved53;	//0xC902A620
	UINT32                                                   reserved54;	//0xC902A624
	UINT32                                                   reserved55;	//0xC902A628
	UINT32                                                   reserved56;	//0xC902A62C
	UINT32                                                   reserved57;	//0xC902A630
	UINT32                                                   reserved58;	//0xC902A634
	UINT32                                                   reserved59;	//0xC902A638
	UINT32                                                   reserved60;	//0xC902A63C
	PE_E60_VCP_WCP_M_PIXEL_READ_DATA_0_T vcp_wcp_m_pixel_read_data_0;	//0xC902A640
	PE_E60_VCP_WCP_M_PIXEL_READ_DATA_1_T vcp_wcp_m_pixel_read_data_1;	//0xC902A644
	PE_E60_VCP_WCP_M_PIXEL_READ_DATA_2_T vcp_wcp_m_pixel_read_data_2;	//0xC902A648
	PE_E60_VCP_WCP_M_PIXEL_READ_DATA_3_T vcp_wcp_m_pixel_read_data_3;	//0xC902A64C
	UINT32                                                   reserved61;	//0xC902A650
	UINT32                                                   reserved62;	//0xC902A654
	UINT32                                                   reserved63;	//0xC902A658
	UINT32                                                   reserved64;	//0xC902A65C
	PE_E60_VCP_SG_BDR_V0_PARAM_POS_M_T  vcp_sg_bdr_v0_param_pos_m;	//0xC902A660
	PE_E60_VCP_SG_BDR_V0_PARAM_SIZE_M_T vcp_sg_bdr_v0_param_size_m;	//0xC902A664
	PE_E60_VCP_SG_BDR_V1_PARAM_POS_M_T  vcp_sg_bdr_v1_param_pos_m;	//0xC902A668
	PE_E60_VCP_SG_BDR_V1_PARAM_SIZE_M_T vcp_sg_bdr_v1_param_size_m;	//0xC902A66C
	UINT32                                                   reserved65;	//0xC902A670
	UINT32                                                   reserved66;	//0xC902A674
	UINT32                                                   reserved67;	//0xC902A678
	UINT32                                                   reserved68;	//0xC902A67C
	PE_E60_VCP_SG_BDR_V0_0_M_CTRL_0_T    vcp_sg_bdr_v0_0_m_ctrl_0;	//0xC902A680
	PE_E60_VCP_SG_BDR_V0_0_M_CTRL_1_T    vcp_sg_bdr_v0_0_m_ctrl_1;	//0xC902A684
	PE_E60_VCP_SG_BDR_V0_0_M_CTRL_2_T    vcp_sg_bdr_v0_0_m_ctrl_2;	//0xC902A688
	UINT32                                                   reserved69;	//0xC902A68C
	PE_E60_VCP_SG_BDR_V0_1_M_CTRL_0_T    vcp_sg_bdr_v0_1_m_ctrl_0;	//0xC902A690
	PE_E60_VCP_SG_BDR_V0_1_M_CTRL_1_T    vcp_sg_bdr_v0_1_m_ctrl_1;	//0xC902A694
	PE_E60_VCP_SG_BDR_V0_1_M_CTRL_2_T    vcp_sg_bdr_v0_1_m_ctrl_2;	//0xC902A698
	UINT32                                                   reserved70;	//0xC902A69C
	PE_E60_VCP_SG_BDR_V0_2_M_CTRL_0_T    vcp_sg_bdr_v0_2_m_ctrl_0;	//0xC902A6A0
	PE_E60_VCP_SG_BDR_V0_2_M_CTRL_1_T    vcp_sg_bdr_v0_2_m_ctrl_1;	//0xC902A6A4
	PE_E60_VCP_SG_BDR_V0_2_M_CTRL_2_T    vcp_sg_bdr_v0_2_m_ctrl_2;	//0xC902A6A8
	UINT32                                                   reserved71;	//0xC902A6AC
	PE_E60_VCP_SG_BDR_V0_3_M_CTRL_0_T    vcp_sg_bdr_v0_3_m_ctrl_0;	//0xC902A6B0
	PE_E60_VCP_SG_BDR_V0_3_M_CTRL_1_T    vcp_sg_bdr_v0_3_m_ctrl_1;	//0xC902A6B4
	PE_E60_VCP_SG_BDR_V0_3_M_CTRL_2_T    vcp_sg_bdr_v0_3_m_ctrl_2;	//0xC902A6B8
	UINT32                                                   reserved72;	//0xC902A6BC
	PE_E60_VCP_SG_BDR_V1_0_M_CTRL_0_T    vcp_sg_bdr_v1_0_m_ctrl_0;	//0xC902A6C0
	PE_E60_VCP_SG_BDR_V1_0_M_CTRL_1_T    vcp_sg_bdr_v1_0_m_ctrl_1;	//0xC902A6C4
	PE_E60_VCP_SG_BDR_V1_0_M_CTRL_2_T    vcp_sg_bdr_v1_0_m_ctrl_2;	//0xC902A6C8
	UINT32                                                   reserved73;	//0xC902A6CC
	PE_E60_VCP_SG_BDR_V1_1_M_CTRL_0_T    vcp_sg_bdr_v1_1_m_ctrl_0;	//0xC902A6D0
	PE_E60_VCP_SG_BDR_V1_1_M_CTRL_1_T    vcp_sg_bdr_v1_1_m_ctrl_1;	//0xC902A6D4
	PE_E60_VCP_SG_BDR_V1_1_M_CTRL_2_T    vcp_sg_bdr_v1_1_m_ctrl_2;	//0xC902A6D8
	UINT32                                                   reserved74;	//0xC902A6DC
	PE_E60_VCP_SG_BDR_V1_2_M_CTRL_0_T    vcp_sg_bdr_v1_2_m_ctrl_0;	//0xC902A6E0
	PE_E60_VCP_SG_BDR_V1_2_M_CTRL_1_T    vcp_sg_bdr_v1_2_m_ctrl_1;	//0xC902A6E4
	PE_E60_VCP_SG_BDR_V1_2_M_CTRL_2_T    vcp_sg_bdr_v1_2_m_ctrl_2;	//0xC902A6E8
	UINT32                                                   reserved75;	//0xC902A6EC
	PE_E60_VCP_SG_BDR_V1_3_M_CTRL_0_T    vcp_sg_bdr_v1_3_m_ctrl_0;	//0xC902A6F0
	PE_E60_VCP_SG_BDR_V1_3_M_CTRL_1_T    vcp_sg_bdr_v1_3_m_ctrl_1;	//0xC902A6F4
	PE_E60_VCP_SG_BDR_V1_3_M_CTRL_2_T    vcp_sg_bdr_v1_3_m_ctrl_2;	//0xC902A6F8
	UINT32                                                   reserved76;	//0xC902A6FC
	PE_E60_VCP_SG_BDR_V0_4_M_CTRL_0_T    vcp_sg_bdr_v0_4_m_ctrl_0;	//0xC902A700
	PE_E60_VCP_SG_BDR_V0_4_M_CTRL_1_T    vcp_sg_bdr_v0_4_m_ctrl_1;	//0xC902A704
	PE_E60_VCP_SG_BDR_V0_4_M_CTRL_2_T    vcp_sg_bdr_v0_4_m_ctrl_2;	//0xC902A708
	UINT32                                                   reserved77;	//0xC902A70C
	PE_E60_VCP_SG_BDR_V0_5_M_CTRL_0_T    vcp_sg_bdr_v0_5_m_ctrl_0;	//0xC902A710
	PE_E60_VCP_SG_BDR_V0_5_M_CTRL_1_T    vcp_sg_bdr_v0_5_m_ctrl_1;	//0xC902A714
	PE_E60_VCP_SG_BDR_V0_5_M_CTRL_2_T    vcp_sg_bdr_v0_5_m_ctrl_2;	//0xC902A718
	UINT32                                                   reserved78;	//0xC902A71C
	PE_E60_VCP_SG_BDR_V0_6_M_CTRL_0_T    vcp_sg_bdr_v0_6_m_ctrl_0;	//0xC902A720
	PE_E60_VCP_SG_BDR_V0_6_M_CTRL_1_T    vcp_sg_bdr_v0_6_m_ctrl_1;	//0xC902A724
	PE_E60_VCP_SG_BDR_V0_6_M_CTRL_2_T    vcp_sg_bdr_v0_6_m_ctrl_2;	//0xC902A728
	UINT32                                                   reserved79;	//0xC902A72C
	PE_E60_VCP_SG_BDR_V0_7_M_CTRL_0_T    vcp_sg_bdr_v0_7_m_ctrl_0;	//0xC902A730
	PE_E60_VCP_SG_BDR_V0_7_M_CTRL_1_T    vcp_sg_bdr_v0_7_m_ctrl_1;	//0xC902A734
	PE_E60_VCP_SG_BDR_V0_7_M_CTRL_2_T    vcp_sg_bdr_v0_7_m_ctrl_2;	//0xC902A738
	UINT32                                                   reserved80;	//0xC902A73C
	PE_E60_VCP_SG_BDR_V1_4_M_CTRL_0_T    vcp_sg_bdr_v1_4_m_ctrl_0;	//0xC902A740
	PE_E60_VCP_SG_BDR_V1_4_M_CTRL_1_T    vcp_sg_bdr_v1_4_m_ctrl_1;	//0xC902A744
	PE_E60_VCP_SG_BDR_V1_4_M_CTRL_2_T    vcp_sg_bdr_v1_4_m_ctrl_2;	//0xC902A748
	UINT32                                                   reserved81;	//0xC902A74C
	PE_E60_VCP_SG_BDR_V1_5_M_CTRL_0_T    vcp_sg_bdr_v1_5_m_ctrl_0;	//0xC902A750
	PE_E60_VCP_SG_BDR_V1_5_M_CTRL_1_T    vcp_sg_bdr_v1_5_m_ctrl_1;	//0xC902A754
	PE_E60_VCP_SG_BDR_V1_5_M_CTRL_2_T    vcp_sg_bdr_v1_5_m_ctrl_2;	//0xC902A758
	UINT32                                                   reserved82;	//0xC902A75C
	PE_E60_VCP_SG_BDR_V1_6_M_CTRL_0_T    vcp_sg_bdr_v1_6_m_ctrl_0;	//0xC902A760
	PE_E60_VCP_SG_BDR_V1_6_M_CTRL_1_T    vcp_sg_bdr_v1_6_m_ctrl_1;	//0xC902A764
	PE_E60_VCP_SG_BDR_V1_6_M_CTRL_2_T    vcp_sg_bdr_v1_6_m_ctrl_2;	//0xC902A768
	UINT32                                                   reserved83;	//0xC902A76C
	PE_E60_VCP_SG_BDR_V1_7_M_CTRL_0_T    vcp_sg_bdr_v1_7_m_ctrl_0;	//0xC902A770
	PE_E60_VCP_SG_BDR_V1_7_M_CTRL_1_T    vcp_sg_bdr_v1_7_m_ctrl_1;	//0xC902A774
	PE_E60_VCP_SG_BDR_V1_7_M_CTRL_2_T    vcp_sg_bdr_v1_7_m_ctrl_2;	//0xC902A778
	UINT32                                                   reserved84;	//0xC902A77C
	PE_E60_VCP_WCP_M_REC5_POS_X_T            vcp_wcp_m_rec5_pos_x;	//0xC902A780
	PE_E60_VCP_WCP_M_REC5_POS_Y_T            vcp_wcp_m_rec5_pos_y;	//0xC902A784
	PE_E60_VCP_WCP_M_REC5_CLR_T                vcp_wcp_m_rec5_clr;	//0xC902A788
	PE_E60_VCP_WCP_M_REC6_POS_X_T            vcp_wcp_m_rec6_pos_x;	//0xC902A78C
	PE_E60_VCP_WCP_M_REC6_POS_Y_T            vcp_wcp_m_rec6_pos_y;	//0xC902A790
	PE_E60_VCP_WCP_M_REC6_CLR_T                vcp_wcp_m_rec6_clr;	//0xC902A794
	PE_E60_VCP_WCP_M_REC7_POS_X_T            vcp_wcp_m_rec7_pos_x;	//0xC902A798
	PE_E60_VCP_WCP_M_REC7_POS_Y_T            vcp_wcp_m_rec7_pos_y;	//0xC902A79C
	PE_E60_VCP_WCP_M_REC7_CLR_T                vcp_wcp_m_rec7_clr;	//0xC902A7A0
	PE_E60_VCP_WCP_M_REC8_POS_X_T            vcp_wcp_m_rec8_pos_x;	//0xC902A7A4
	PE_E60_VCP_WCP_M_REC8_POS_Y_T            vcp_wcp_m_rec8_pos_y;	//0xC902A7A8
	PE_E60_VCP_WCP_M_REC8_CLR_T                vcp_wcp_m_rec8_clr;	//0xC902A7AC
	PE_E60_VCP_WCP_M_REC9_POS_X_T            vcp_wcp_m_rec9_pos_x;	//0xC902A7B0
	PE_E60_VCP_WCP_M_REC9_POS_Y_T            vcp_wcp_m_rec9_pos_y;	//0xC902A7B4
	PE_E60_VCP_WCP_M_REC9_CLR_T                vcp_wcp_m_rec9_clr;	//0xC902A7B8
	UINT32                                                   reserved85;	//0xC902A7BC
	UINT32                                                   reserved86;	//0xC902A7C0
	PE_E60_VCP_WCP_MS_CTRL_10_T                vcp_wcp_ms_ctrl_10;	//0xC902A7C4
	UINT32                                                   reserved87;	//0xC902A7C8
	UINT32                                                   reserved88;	//0xC902A7CC
	UINT32                                                   reserved89;	//0xC902A7D0
	UINT32                                                   reserved90;	//0xC902A7D4
	UINT32                                                   reserved91;	//0xC902A7D8
	UINT32                                                   reserved92;	//0xC902A7DC
	UINT32                                                   reserved93;	//0xC902A7E0
	UINT32                                                   reserved94;	//0xC902A7E4
	UINT32                                                   reserved95;	//0xC902A7E8
	UINT32                                                   reserved96;	//0xC902A7EC
	UINT32                                                   reserved97;	//0xC902A7F0
	UINT32                                                   reserved98;	//0xC902A7F4
	UINT32                                                   reserved99;	//0xC902A7F8
	UINT32                                                  reserved100;	//0xC902A7FC
	PE_E60_VCP_WCP_ALPHA_CTRL_T                vcp_wcp_alpha_ctrl;	//0xC902A800
	PE_E60_VCP_WCP_ALPHA_GEN_Y_0_T          vcp_wcp_alpha_gen_y_0;	//0xC902A804
	PE_E60_VCP_WCP_ALPHA_GEN_Y_1_T          vcp_wcp_alpha_gen_y_1;	//0xC902A808
	PE_E60_VCP_WCP_ALPHA_GEN_Y_2_T          vcp_wcp_alpha_gen_y_2;	//0xC902A80C
	PE_E60_VCP_WCP_ALPHA_GEN_Y_3_T          vcp_wcp_alpha_gen_y_3;	//0xC902A810
	PE_E60_VCP_WCP_ALPHA_GEN_Y_4_T          vcp_wcp_alpha_gen_y_4;	//0xC902A814
	PE_E60_VCP_WCP_ALPHA_GEN_Y_5_T          vcp_wcp_alpha_gen_y_5;	//0xC902A818
	PE_E60_VCP_WCP_ALPHA_GEN_C_0_T          vcp_wcp_alpha_gen_c_0;	//0xC902A81C
	PE_E60_VCP_WCP_ALPHA_GEN_C_1_T          vcp_wcp_alpha_gen_c_1;	//0xC902A820
	PE_E60_VCP_WCP_ALPHA_GEN_C_2_T          vcp_wcp_alpha_gen_c_2;	//0xC902A824
	PE_E60_VCP_WCP_ALPHA_GEN_C_3_T          vcp_wcp_alpha_gen_c_3;	//0xC902A828
	PE_E60_VCP_WCP_ALPHA_GEN_C_4_T          vcp_wcp_alpha_gen_c_4;	//0xC902A82C
	PE_E60_VCP_WCP_ALPHA_GEN_C_5_T          vcp_wcp_alpha_gen_c_5;	//0xC902A830
	PE_E60_VCP_WCP_M_REC2_POS_X_T            vcp_wcp_m_rec2_pos_x;	//0xC902A834
	PE_E60_VCP_WCP_M_REC2_POS_Y_T            vcp_wcp_m_rec2_pos_y;	//0xC902A838
	PE_E60_VCP_WCP_M_REC3_POS_X_T            vcp_wcp_m_rec3_pos_x;	//0xC902A83C
	PE_E60_VCP_WCP_M_REC3_POS_Y_T            vcp_wcp_m_rec3_pos_y;	//0xC902A840
	PE_E60_VCP_WCP_M_REC4_POS_X_T            vcp_wcp_m_rec4_pos_x;	//0xC902A844
	PE_E60_VCP_WCP_M_REC4_POS_Y_T            vcp_wcp_m_rec4_pos_y;	//0xC902A848
	PE_E60_VCP_WCP_M_REC0_CLR_T                vcp_wcp_m_rec0_clr;	//0xC902A84C
	PE_E60_VCP_WCP_M_REC1_CLR_T                vcp_wcp_m_rec1_clr;	//0xC902A850
	PE_E60_VCP_WCP_M_REC2_CLR_T                vcp_wcp_m_rec2_clr;	//0xC902A854
	PE_E60_VCP_WCP_M_REC3_CLR_T                vcp_wcp_m_rec3_clr;	//0xC902A858
	PE_E60_VCP_WCP_M_REC4_CLR_T                vcp_wcp_m_rec4_clr;	//0xC902A85C
	PE_E60_VCP_VSP_U0_CTRL_00_T                vcp_vsp_u0_ctrl_00;	//0xC902A860
	PE_E60_VCP_VSP_U0_CTRL_01_T                vcp_vsp_u0_ctrl_01;	//0xC902A864
	PE_E60_VCP_VSP_U1_CTRL_00_T                vcp_vsp_u1_ctrl_00;	//0xC902A868
	PE_E60_VCP_VSP_U1_CTRL_01_T                vcp_vsp_u1_ctrl_01;	//0xC902A86C
	PE_E60_VCP_CRC_CTRL_T                            vcp_crc_ctrl;	//0xC902A870
	PE_E60_VCP_CRC_DATA_MASK0_T                vcp_crc_data_mask0;	//0xC902A874
	PE_E60_VCP_CRC_DATA_MASK1_T                vcp_crc_data_mask1;	//0xC902A878
	UINT32                                                  reserved101;	//0xC902A87C
	UINT32                                                  reserved102;	//0xC902A880
	PE_E60_VCP_CRC_OUT0_T                            vcp_crc_out0;	//0xC902A884
	PE_E60_VCP_CRC_OUT1_T                            vcp_crc_out1;	//0xC902A888
	UINT32                                                  reserved103;	//0xC902A88C
	UINT32                                                  reserved104;	//0xC902A890
	UINT32                                                  reserved105;	//0xC902A894
	UINT32                                                  reserved106;	//0xC902A898
	UINT32                                                  reserved107;	//0xC902A89C
	PE_E60_VCP_SG_MVY_CTRL_A_T                  vcp_sg_mvy_ctrl_a;	//0xC902A8A0
	PE_E60_VCP_SG_MVC_CTRL_A_T                  vcp_sg_mvc_ctrl_a;	//0xC902A8A4
	PE_E60_VCP_SG_SVY_CTRL_A_T                  vcp_sg_svy_ctrl_a;	//0xC902A8A8
	PE_E60_VCP_SG_SVC_CTRL_A_T                  vcp_sg_svc_ctrl_a;	//0xC902A8AC
	UINT32                                                  reserved108;	//0xC902A8B0
	UINT32                                                  reserved109;	//0xC902A8B4
	UINT32                                                  reserved110;	//0xC902A8B8
	UINT32                                                  reserved111;	//0xC902A8BC
	UINT32                                                  reserved112;	//0xC902A8C0
	UINT32                                                  reserved113;	//0xC902A8C4
	UINT32                                                  reserved114;	//0xC902A8C8
	UINT32                                                  reserved115;	//0xC902A8CC
	UINT32                                                  reserved116;	//0xC902A8D0
	UINT32                                                  reserved117;	//0xC902A8D4
	UINT32                                                  reserved118;	//0xC902A8D8
	UINT32                                                  reserved119;	//0xC902A8DC
	UINT32                                                  reserved120;	//0xC902A8E0
	UINT32                                                  reserved121;	//0xC902A8E4
	UINT32                                                  reserved122;	//0xC902A8E8
	UINT32                                                  reserved123;	//0xC902A8EC
	UINT32                                                  reserved124;	//0xC902A8F0
	UINT32                                                  reserved125;	//0xC902A8F4
	UINT32                                                  reserved126;	//0xC902A8F8
	UINT32                                                  reserved127;	//0xC902A8FC
	PE_E60_VCP_DISP_INTR_MASK_T                vcp_disp_intr_mask;	//0xC902A900
	PE_E60_VCP_DISP_INTR_CLEAR_T              vcp_disp_intr_clear;	//0xC902A904
	PE_E60_VCP_DISP_INTR_STATUS_T            vcp_disp_intr_status;	//0xC902A908
	PE_E60_VCP_DISP_INTR0_POS_MV_Y_T      vcp_disp_intr0_pos_mv_y;	//0xC902A90C
	PE_E60_VCP_DISP_INTR1_POS_MV_Y_T      vcp_disp_intr1_pos_mv_y;	//0xC902A910
	PE_E60_VCP_DISP_INTR0_POS_MV_C_T      vcp_disp_intr0_pos_mv_c;	//0xC902A914
	PE_E60_VCP_DISP_INTR1_POS_MV_C_T      vcp_disp_intr1_pos_mv_c;	//0xC902A918
	PE_E60_VCP_DISP_INTR0_POS_SV_Y_T      vcp_disp_intr0_pos_sv_y;	//0xC902A91C
	PE_E60_VCP_DISP_INTR1_POS_SV_Y_T      vcp_disp_intr1_pos_sv_y;	//0xC902A920
	PE_E60_VCP_DISP_INTR0_POS_SV_C_T      vcp_disp_intr0_pos_sv_c;	//0xC902A924
	PE_E60_VCP_DISP_INTR1_POS_SV_C_T      vcp_disp_intr1_pos_sv_c;	//0xC902A928
	PE_E60_VCP_DISP_INTR_SRC_SEL_T          vcp_disp_intr_src_sel;	//0xC902A92C
	PE_E60_VCP_U0_CSC_CTRL7_T                    vcp_u0_csc_ctrl7;	//0xC902A930
	PE_E60_VCP_U1_CSC_CTRL0_T                    vcp_u1_csc_ctrl0;	//0xC902A934
	PE_E60_VCP_U1_CSC_CTRL1_T                    vcp_u1_csc_ctrl1;	//0xC902A938
	PE_E60_VCP_U1_CSC_CTRL2_T                    vcp_u1_csc_ctrl2;	//0xC902A93C
	PE_E60_VCP_U1_CSC_CTRL3_T                    vcp_u1_csc_ctrl3;	//0xC902A940
	PE_E60_VCP_U1_CSC_CTRL4_T                    vcp_u1_csc_ctrl4;	//0xC902A944
	PE_E60_VCP_U1_CSC_CTRL5_T                    vcp_u1_csc_ctrl5;	//0xC902A948
	PE_E60_VCP_U1_CSC_CTRL6_T                    vcp_u1_csc_ctrl6;	//0xC902A94C
	PE_E60_VCP_U1_CSC_CTRL7_T                    vcp_u1_csc_ctrl7;	//0xC902A950
	PE_E60_VCP_ACTIVE_LINE_CNT_T              vcp_active_line_cnt;	//0xC902A954
	UINT32                                                  reserved128;	//0xC902A958
	UINT32                                                  reserved129;	//0xC902A95C
	UINT32                                                  reserved130;	//0xC902A960
	UINT32                                                  reserved131;	//0xC902A964
	UINT32                                                  reserved132;	//0xC902A968
	UINT32                                                  reserved133;	//0xC902A96C
	UINT32                                                  reserved134;	//0xC902A970
	UINT32                                                  reserved135;	//0xC902A974
	UINT32                                                  reserved136;	//0xC902A978
	UINT32                                                  reserved137;	//0xC902A97C
	UINT32                                                  reserved138;	//0xC902A980
	UINT32                                                  reserved139;	//0xC902A984
	UINT32                                                  reserved140;	//0xC902A988
	UINT32                                                  reserved141;	//0xC902A98C
	UINT32                                                  reserved142;	//0xC902A990
	UINT32                                                  reserved143;	//0xC902A994
	UINT32                                                  reserved144;	//0xC902A998
	UINT32                                                  reserved145;	//0xC902A99C
	UINT32                                                  reserved146;	//0xC902A9A0
	UINT32                                                  reserved147;	//0xC902A9A4
	UINT32                                                  reserved148;	//0xC902A9A8
	UINT32                                                  reserved149;	//0xC902A9AC
	UINT32                                                  reserved150;	//0xC902A9B0
	UINT32                                                  reserved151;	//0xC902A9B4
	UINT32                                                  reserved152;	//0xC902A9B8
	UINT32                                                  reserved153;	//0xC902A9BC
	UINT32                                                  reserved154;	//0xC902A9C0
	UINT32                                                  reserved155;	//0xC902A9C4
	UINT32                                                  reserved156;	//0xC902A9C8
	UINT32                                                  reserved157;	//0xC902A9CC
	UINT32                                                  reserved158;	//0xC902A9D0
	UINT32                                                  reserved159;	//0xC902A9D4
	UINT32                                                  reserved160;	//0xC902A9D8
	UINT32                                                  reserved161;	//0xC902A9DC
	UINT32                                                  reserved162;	//0xC902A9E0
	UINT32                                                  reserved163;	//0xC902A9E4
	UINT32                                                  reserved164;	//0xC902A9E8
	UINT32                                                  reserved165;	//0xC902A9EC
	UINT32                                                  reserved166;	//0xC902A9F0
	UINT32                                                  reserved167;	//0xC902A9F4
	UINT32                                                  reserved168;	//0xC902A9F8
	UINT32                                                  reserved169;	//0xC902A9FC
	UINT32                                                  reserved170;	//0xC902AA00
	UINT32                                                  reserved171;	//0xC902AA04
	UINT32                                                  reserved172;	//0xC902AA08
	UINT32                                                  reserved173;	//0xC902AA0C
	UINT32                                                  reserved174;	//0xC902AA10
	UINT32                                                  reserved175;	//0xC902AA14
	UINT32                                                  reserved176;	//0xC902AA18
	UINT32                                                  reserved177;	//0xC902AA1C
	UINT32                                                  reserved178;	//0xC902AA20
	UINT32                                                  reserved179;	//0xC902AA24
	UINT32                                                  reserved180;	//0xC902AA28
	UINT32                                                  reserved181;	//0xC902AA2C
	UINT32                                                  reserved182;	//0xC902AA30
	UINT32                                                  reserved183;	//0xC902AA34
	UINT32                                                  reserved184;	//0xC902AA38
	UINT32                                                  reserved185;	//0xC902AA3C
	UINT32                                                  reserved186;	//0xC902AA40
	UINT32                                                  reserved187;	//0xC902AA44
	UINT32                                                  reserved188;	//0xC902AA48
	UINT32                                                  reserved189;	//0xC902AA4C
	UINT32                                                  reserved190;	//0xC902AA50
	UINT32                                                  reserved191;	//0xC902AA54
	UINT32                                                  reserved192;	//0xC902AA58
	UINT32                                                  reserved193;	//0xC902AA5C
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_00_T      shp_motion_gain_ctrl_00;	//0xC902AA60
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_01_T      shp_motion_gain_ctrl_01;	//0xC902AA64
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_02_T      shp_motion_gain_ctrl_02;	//0xC902AA68
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_03_T      shp_motion_gain_ctrl_03;	//0xC902AA6C
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_04_T      shp_motion_gain_ctrl_04;	//0xC902AA70
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_05_T      shp_motion_gain_ctrl_05;	//0xC902AA74
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_06_T      shp_motion_gain_ctrl_06;	//0xC902AA78
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_07_T      shp_motion_gain_ctrl_07;	//0xC902AA7C
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_08_T      shp_motion_gain_ctrl_08;	//0xC902AA80
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_09_T      shp_motion_gain_ctrl_09;	//0xC902AA84
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0A_T      shp_motion_gain_ctrl_0a;	//0xC902AA88
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0B_T      shp_motion_gain_ctrl_0b;	//0xC902AA8C
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0C_T      shp_motion_gain_ctrl_0c;	//0xC902AA90
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0D_T      shp_motion_gain_ctrl_0d;	//0xC902AA94
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0E_T      shp_motion_gain_ctrl_0e;	//0xC902AA98
	REG_VCP_DISP_SHP_MOTION_GAIN_CTRL_0F_T      shp_motion_gain_ctrl_0f;	//0xC902AA9C
	REG_VCP_DISP_SHP_MOTION_GAIN_STAT_00_T      shp_motion_gain_stat_00;	//0xC902AAA0
	REG_VCP_DISP_SHP_MOTION_GAIN_STAT_01_T      shp_motion_gain_stat_01;	//0xC902AAA4
}PE_VCP_DISP_REG_E60_T;


typedef union {
	UINT32 udata32;
	struct {						//0xC9029800 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_E60_VSD0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029804 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029808 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_VSD0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902980C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_VSD0_VERI_SYS_VERI_3_T;

typedef struct {
	PE_E60_VSD0_VERI_SYS_VERI_0_T                          vsd0_veri_vsp_0;	//0xC9029800
	PE_E60_VSD0_VERI_SYS_VERI_1_T                          vsd0_veri_vsp_1;	//0xC9029804
	PE_E60_VSD0_VERI_SYS_VERI_2_T                               sys_veri_2;	//0xC9029808
	PE_E60_VSD0_VERI_SYS_VERI_3_T                               sys_veri_3;	//0xC902980C
}PE_VSD0_VERI_REG_E60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CF00 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}REG_VSD1_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CF04 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}REG_VSD1_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CF08 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_VSD1_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CF0C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_VSD1_VERI_SYS_VERI_3_T;

typedef struct {
	REG_VSD1_VERI_SYS_VERI_0_T                          vsd1_veri_vsp_0;	//0xC902CF00
	REG_VSD1_VERI_SYS_VERI_1_T                          vsd1_veri_vsp_1;	//0xC902CF04
	REG_VSD1_VERI_SYS_VERI_2_T                               sys_veri_2;	//0xC902CF08
	REG_VSD1_VERI_SYS_VERI_3_T                               sys_veri_3;	//0xC902CF0C
}PE_VSD1_VERI_REG_E60_T;

#endif